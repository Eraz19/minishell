#ifndef SCANNER_H
# define SCANNER_H

# include "error.h"
# include "token.h"
# include "lexer.h"
# include "input_mode.h"

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
	t_error			err;
	t_input_mode	mode;
	t_lexer			lexer;
	const char		*source;
}	t_scanner;

/* ************************************************************************* */
/*                                LIFE_CYCLE                                 */
/* ************************************************************************* */

/**
 * @ingroup scanner
 * @brief Zeroes @p scanner and initializes its lexer state.
 *
 * @param scanner Scanner initialized by the function (borrowed).
 * @return @c ERR_NO.
 */
t_error	scanner_init(t_scanner *scanner);

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

// TODO: doc
void	scanner_clear(t_scanner *scanner);

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

t_error	scanner_set_cmd_sub_input(const t_string *cmd_string);

void	scanner_cmd_sub_free(t_scanner *cmd_sub_scanner);
t_error	scanner_cmd_sub_init(
			const t_scanner *main_scanner,
			t_scanner *cmd_sub_scanner);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

t_error	scanner_get_next_token(t_scanner *scanner, t_token *token);

t_error	scanner_read_heredoc(
			t_scanner *scanner,
			t_string *out,
			const t_token *delim,
			bool strip);

#endif
