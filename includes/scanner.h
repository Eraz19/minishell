#ifndef SCANNER_H
# define SCANNER_H

# include "error.h"
# include "lexer.h"

/* ************************************************************************* */
/*                             TYPE FORWARDING                               */
/* ************************************************************************* */

typedef struct s_parser	t_parser;

/* ************************************************************************* */
/*                                  TYPES                                    */
/* ************************************************************************* */

/**
 * @ingroup scanner
 * @enum e_scan_mode
 * @brief Input acquisition mode of a scanner, fixed at @ref scanner_load.
 *
 * @warning Only @c SCAN_MODE_CMD_SUB and @c SCAN_MODE_STDIN may request
 *          PS2 continuations; every other mode makes
 *          @ref read_and_propagate_PS2 report @c ERR_VEOF.
 *
 * @var e_scan_mode::SCAN_MODE_NONE Unset; state of a freed scanner.
 * @var e_scan_mode::SCAN_MODE_AUTO Requested by the top-level shell run.
 *      @warning No resolution of @c SCAN_MODE_AUTO into
 *      @c SCAN_MODE_FILE / @c SCAN_MODE_STDIN / @c SCAN_MODE_STRING
 *      exists in the tree: a scanner loaded with it binds no source,
 *      matches no reader lane and refuses PS2. TODO: resolve at startup.
 * @var e_scan_mode::SCAN_MODE_FILE Script run: @c source is the script
 *      path, read whole on the first token request.
 * @var e_scan_mode::SCAN_MODE_STDIN Standard input, interactive (PS1/PS2
 *      prompts) or piped (pre-slurped by the reader).
 * @var e_scan_mode::SCAN_MODE_STRING One-shot command text in @c source:
 *      @c -c invocation, @c eval, command substitution children and
 *      internal re-scans (heredoc bodies, expander words).
 * @var e_scan_mode::SCAN_MODE_CMD_SUB Nested scanner lexing a command
 *      substitution over a private copy of the parent scanner input.
 * @var e_scan_mode::SCAN_MODE_STRING_AND_CONTINUE Declared but unused.
 */
typedef enum e_scan_mode
{
	SCAN_MODE_NONE,
	SCAN_MODE_AUTO,
	SCAN_MODE_FILE,
	SCAN_MODE_STDIN,
	SCAN_MODE_STRING,
	SCAN_MODE_CMD_SUB,
	SCAN_MODE_STRING_AND_CONTINUE,
}	t_scan_mode;

/**
 * @ingroup scanner
 * @struct s_scanner
 * @brief Token producer bound to one parser: acquires input per
 *        @ref t_scan_mode, delegates recognition to its lexer and
 *        requalifies the errors leaving the module
 *        (@ref requalify_scanner_error).
 *
 * @var s_scanner::err Last error recorded by a scanner operation; mirror
 *                     of the value returned by the failing call.
 * @var s_scanner::mode Input acquisition mode, fixed at @ref scanner_load.
 * @var s_scanner::lexer Token recognizer state, managed by the lexer
 *                       submodule.
 * @var s_scanner::source Script path (@c SCAN_MODE_FILE) or command text
 *                        (@c SCAN_MODE_STRING); bound from the params
 *                        source at load, rebound by
 *                        @ref scanner_bind_input (borrowed, read-only).
 * @var s_scanner::parser Parser consuming the tokens; queried for the
 *                        alias position check (borrowed).
 * @var s_scanner::parent_scanner Scanner this @c SCAN_MODE_CMD_SUB
 *                                scanner was forked from (borrowed).
 */
typedef struct s_scanner
{
	t_error		err;
	t_scan_mode	mode;
	t_lexer		lexer;
	const char	*source;
	t_parser	*parser;			// borrowed
	t_scanner	*parent_scanner; 	// borrowed
}	t_scanner;

/* ************************************************************************* */
/*                                LIFE_CYCLE                                 */
/* ************************************************************************* */

/**
 * @ingroup scanner
 * @brief Zeroes @p scanner and initializes its lexer.
 *
 * @param scanner Scanner to initialize (borrowed).
 */
void	scanner_init(t_scanner *scanner);

/**
 * @ingroup scanner
 * @brief Binds @p scanner to @p parser and @p mode, re-initializes the
 *        lexer, installs the readline hooks, binds the params source as
 *        @c source for @c SCAN_MODE_STRING / @c SCAN_MODE_FILE and, for
 *        @c SCAN_MODE_CMD_SUB, deep-copies @p parent_scanner's input
 *        stack.
 *
 * @param scanner Already initialized scanner (borrowed).
 * @param parent_scanner Scanner to fork the input from; only read for
 *                       @c SCAN_MODE_CMD_SUB (borrowed).
 * @param parser Parser consuming the tokens (borrowed).
 * @param mode Input acquisition mode.
 * @return @c ERR_NO on success; @c ERR_LIBC (@c SCAN_MODE_CMD_SUB input
 *         stack duplication failed) on module-produced failure.
 *         Module-external errors (shell instance lookup) bubble through
 *         unlisted.
 */
t_error	scanner_load(t_scanner *scanner, t_scanner *parent_scanner, t_parser *parser, t_scan_mode mode);

/**
 * @ingroup scanner
 * @brief Releases the lexer state and unbinds every borrowed pointer.
 *
 * @param scanner Scanner to release; reusable after @ref scanner_load
 *                (borrowed).
 */
void	scanner_free(t_scanner *scanner);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup scanner
 * @brief Clears the lexer state and binds @p cmd_string's text as the
 *        new @c source.
 *
 * @note The mode is left untouched: the caller is expected to run the
 *       scanner in @c SCAN_MODE_STRING over @p cmd_string.
 *
 * @param scanner Already loaded scanner (borrowed).
 * @param cmd_string Command text to scan; must outlive the scanner use
 *                   (borrowed, read-only).
 */
void	scanner_bind_input(t_scanner *scanner, const t_string *cmd_string);

/**
 * @ingroup scanner
 * @brief Clears the lexer state (input stack and pending token) without
 *        unbinding the scanner.
 *
 * @param scanner Scanner to clear (borrowed).
 */
void	scanner_clear(t_scanner *scanner);

/**
 * @ingroup scanner
 * @brief Produces the next token: stacks new input when needed (or a PS2
 *        continuation when @p ps2 is set), delegates to
 *        @ref lexer_get_next_token and expands the result through
 *        @ref expand_alias when it is a word.
 *
 * @warning @c ERR_VEOF leaves the scanner verbatim (exit contract,
 *          @ref requalify_scanner_error) and only means "interactive
 *          input ended between tokens" (@c CTRL+D at PS1): a continuation
 *          impossible in @c SCAN_MODE_FILE / @c SCAN_MODE_STRING is
 *          reported as @c ERR_POSIX_SYNTAX at production, and any
 *          end-of-continuation while a construct is open — @c CTRL+D at
 *          PS2 included — is converted into the printed unterminated
 *          diagnostic (@ref on_context_scan_EOI).
 * @warning The alias lane depends on @c env_get_alias, currently an
 *          unresolved symbol (env branch, resolves at merge): its error
 *          set is incomplete until then. Ineligible words and lookup
 *          misses pass through as plain words (see @ref expand_alias).
 *
 * @param scanner Already loaded scanner (borrowed).
 * @param out Receives the token; initialized by the function, untouched
 *            when input acquisition fails. The caller releases it with
 *            @ref token_free (borrowed).
 * @param ps2 True to grow the current input with a PS2 continuation
 *            instead of stacking a new one.
 * @return @c ERR_NO on success. Module-produced failures, after
 *         @ref requalify_scanner_error:
 *         @c ERR_VEOF (end of input, verbatim on every lane),
 *         @c ERR_POSIX_SYNTAX (printed, unterminated
 *         construct), @c ERR_POSIX_READ, @c ERR_POSIX_CMD_NOT_FOUND and
 *         @c ERR_POSIX_CMD_NOT_EXECUTABLE (printed, @c SCAN_MODE_FILE
 *         acquisition) or @c ERR_LIBC (module allocation / libc failure).
 *         Module-external errors (params, sig, embedded
 *         command-substitution parse, alias position check) bubble
 *         through unlisted, printed at the frontier when still unprinted.
 */
t_error	scanner_get_next_token(t_scanner *scanner, t_token *out, bool ps2);

/**
 * @ingroup scanner
 * @brief Reads a here-document body for @p delim through
 *        @ref heredoc_read_body and requalifies the result.
 *
 * @note A missing delimiter is absorbed: the heredoc prints the
 *       @c ERR_NO_DELIM diagnostic, reports @c ERR_VEOF and the
 *       qualification turns it into @c ERR_NO (documented choice,
 *       POSIX 2.7.4 "should, but need not, treat this as a redirection
 *       error").
 *
 * @param scanner Already loaded scanner (borrowed).
 * @param out Receives the raw body; initialized by the function on
 *            success, untouched on failure (borrowed).
 * @param delim Delimiter word token (borrowed, read-only).
 * @param strip True for @c <<-: leading tabs stripped from body and
 *              delimiter lines.
 * @return @c ERR_NO on success (including the absorbed missing
 *         delimiter); @c ERR_LIBC (module allocation / libc failure) on
 *         module-produced failure. Module-external errors (delimiter
 *         expansion by the expander, params) bubble through unlisted,
 *         printed at the frontier when still unprinted.
 */
t_error	scanner_read_heredoc(t_scanner *scanner, t_string *out, t_token *delim, bool strip);

#endif
