#ifndef SCANNER_H
# define SCANNER_H

# include "error.h"
# include "token.h"
# include "lexer.h"

typedef struct s_parser	t_parser;

/** @defgroup input_mode Input mode API
 *  @brief Identifies where the shell reads its commands from.
 *
 *  The input mode is derived once at startup from the invocation options
 *  (@c -s, @c -i, @c -c) and drives how the scanner sources its input and
 *  whether interactive behaviour (prompting) is enabled.
 */

/**
 * @ingroup input_mode
 * @enum e_input_mode
 * @brief Source the shell reads its commands from.
 */
typedef enum e_scan_mode
{
	SCAN_MODE_NONE,
	SCAN_MODE_AUTO,
	SCAN_MODE_FILE,
	SCAN_MODE_STRING,
	SCAN_MODE_STDIN_TTY,
	SCAN_MODE_STDIN_PIPE
}	t_scan_mode;

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/** @defgroup scanner Scanner API
 *  @brief Turns raw shell input into a POSIX token stream.
 *
 *  The scanner is the front end of the shell: it reads input incrementally
 *  (from a file, a command string or standard input), drives the lexer to
 *  recognise one token at a time following POSIX token recognition rules
 *  (XCU 2.3), and collects the here-documents the parser reports along the
 *  way. It also triggers alias expansion on word tokens by pushing the
 *  expansion back onto the lexer's input stack.
 *
 *  The scanner owns its lexer state: @ref scanner_init allocates it and
 *  @ref scanner_free releases it.
 *
 *  ERROR CONTRACT
 *
 *  Every endpoint requalifies the errors of its callees before they cross
 *  the API (see @c scanner_error_qualify): the specific diagnostic is
 *  printed at requalification time, so callers must not print scanner
 *  errors again. Only fully qualified error types escape, plus a single
 *  deliberate exception, @c ERR_VEOF:
 *
 *  - @c ERR_VEOF crosses the API raw and unprinted when the input ends at a
 *    point where the exit decision belongs to the caller: at the top-level
 *    prompt of an interactive shell (from @ref scanner_get_next_token) and
 *    while reading a continuation line for a here-document body (from
 *    @ref scanner_read_continuation). It is a control-flow signal, not a
 *    failure: POSIX requires the interactive shell to exit with the exit
 *    status of the last command executed, which only the shell loop knows.
 *  - When the input ends in the middle of a construct instead, @c ERR_VEOF
 *    never escapes: it is requalified as @c ERR_POSIX_SYNTAX like every
 *    other unexpected end of input.
 *
 *  @warning The runner does not yet handle @c ERR_VEOF: it currently
 *           escapes @c runner_run as a fatal error and becomes a garbage
 *           exit status. The shell loop must catch it and exit cleanly
 *           with the exit status of the last command executed.
 *
 *  End of input at the very start of the token stream is not an error:
 *  an empty source (empty script, @c -c with an empty string, empty
 *  standard input) yields a @c TOKEN_EOF token and @c ERR_NO.
 */

/**
 * @ingroup scanner
 * @struct s_scanner
 * @brief Aggregate state of the scanner module.
 *
 * @var s_scanner::err Last error recorded by the module.
 * @var s_scanner::mode Source the input is read from, managed by the
 *                      input_mode submodule.
 * @var s_scanner::lexer Lexer state owned by the scanner, managed by the
 *                       lexer submodule (initialized by @ref scanner_init,
 *                       released by @ref scanner_free).
 * @var s_scanner::source File path or command string for the FILE and
 *                        STRING modes, unused for the STDIN modes
 *                        (borrowed, read-only).
 */
typedef struct s_scanner
{
	t_error		err;
	t_scan_mode	mode;
	t_lexer		lexer;
	const char	*source;
	t_parser	*parser;	// borrowed
}	t_scanner;

/* ************************************************************************* */
/*                                LIFE_CYCLE                                 */
/* ************************************************************************* */

// TODO: doc
// @ret ERR_INTERNAL
t_error	scanner_init(t_scanner *scanner, t_parser *parser, t_scan_mode mode);

/**
 * @ingroup scanner
 * @brief Derives the input mode from the shell invocation options and
 *        records @p source for the FILE and STRING modes.
 *
 * @warning @p source is stored, not copied: it must outlive the scanner.
 * @param scanner Already initialized scanner (borrowed).
 * @param source Script path or command string, ignored for the STDIN
 *               modes (borrowed, read-only).
 * @return @c ERR_INTERNAL (printed) if the shell parameters are
 *         unavailable, @c ERR_NO on success.
 */
t_error	scanner_load(t_scanner *scanner, const char *source);

/**
 * @ingroup scanner
 * @brief Releases the lexer state of @p scanner and zeroes it.
 *
 * @param scanner Already initialized scanner (borrowed).
 */
void	scanner_free(t_scanner *scanner);

/* ************************************************************************* */
/*                                 CMD_SUB                                   */
/* ************************************************************************* */

/**
 * @ingroup scanner
 * @brief Releases a scanner clone built by @ref scanner_cmd_sub_init.
 *
 * @param cmd_sub_scanner Already initialized clone (borrowed).
 */
void	scanner_cmd_sub_free(t_scanner *cmd_sub_scanner);

// TODO: doc
t_error    scanner_cmd_sub_init(
				const t_scanner *main_scanner,
				t_scanner *cmd_sub_scanner,
				t_parser *cmd_sub_parser);

// TODO: doc
void	scanner_set_input(t_scanner *scanner, const t_string *cmd);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup scanner
 * @brief Drops every pending input and the token in progress of the
 *        scanner's lexer, ready for a fresh drive (typically after a
 *        syntax error).
 *
 * @param scanner Already initialized scanner (borrowed).
 */
void	scanner_clear(t_scanner *scanner);

/**
 * @ingroup scanner
 * @brief Produces the next POSIX token: reads input when the stack is
 *        empty, drives the lexer with the recognition rules, and
 *        applies alias substitution to word tokens (re-lexing from the
 *        expansion).
 *
 * @note An exhausted source is not an error: @p token is set to
 *       @c TOKEN_EOF and @c ERR_NO is returned.
 * @param scanner Already initialized and loaded scanner (borrowed).
 * @param token Token initialized by the function; the caller owns it
 *              and must release it with @c token_free (borrowed).
 * @return @c ERR_VEOF (raw, unprinted) at the top-level end of input of
 *         an interactive shell (see the ERROR CONTRACT above);
 *         @c ERR_POSIX_SYNTAX (printed) on an unexpected end of input
 *         inside a construct; @c ERR_POSIX_CMD_NOT_FOUND /
 *         @c ERR_POSIX_CMD_NOT_EXECUTABLE (printed) when the script
 *         file cannot be opened; @c ERR_POSIX_READ (printed) on an
 *         unrecoverable read error; @c ERR_INTERRUPTED when a signal
 *         interrupts the read; @c ERR_LIBC (printed) on allocation
 *         failure; @c ERR_INTERNAL (printed) on any scanner, lexer,
 *         alias or history inconsistency; @c ERR_NO on success.
 */
t_error	scanner_get_next_token(t_scanner *scanner, t_token *token);

/**
 * @ingroup scanner
 * @brief Switches @p scanner to the pipe input mode after a fork, so
 *        the subshell reads its whole standard input regardless of the
 *        parent's mode (see @c shell_init_subshell).
 *
 * sets scanner->mode = SCAN_MODE_STDIN_PIPE
 *
 * @param scanner Already initialized scanner (borrowed).
 */
void	scanner_init_subshell(t_scanner *scanner);

/**
 * @ingroup scanner
 * @brief Reads one here-document body from the current input up to the
 *        delimiter line (POSIX 2.7.4): quote-removes @p delim, then
 *        accumulates lines (prompting for continuation lines on a
 *        terminal), tab-stripping them when @p strip is set.
 *
 * @note The delimiter line is matched on PHYSICAL lines; a trailing
 *       line continuation in the body is removed at expansion time
 *       (documented choice, see the heredoc module).
 * @param scanner Already initialized scanner (borrowed).
 * @param out String receiving the body, initialized by the function on
 *            success only (borrowed).
 * @param delim Raw delimiter token (borrowed, read-only).
 * @param strip Tab-stripping mode of the @c <<- operator.
 * @return @c ERR_POSIX_SYNTAX (printed with the delimiter by the
 *         heredoc) when the input ends before the delimiter line
 *         (documented choice, POSIX 2.7.4 "should, but need not,
 *         treat this as a redirection error"); from the delimiter
 *         quote removal, already qualified by the expander:
 *         @c ERR_POSIX_EXPANSION (printed), @c ERR_INTERNAL (printed)
 *         or @c ERR_INTERRUPTED; @c ERR_LIBC (printed) on allocation
 *         failure; @c ERR_NO on success.
 */
t_error	scanner_read_heredoc(
			t_scanner *scanner,
			t_string *out,
			t_token *delim,
			bool strip);

#endif
