#ifndef SCANNER__H
# define SCANNER__H

# include "scanner.h"
# include "heredoc.h"

/** @defgroup scanner_priv Scanner internals
 *  @brief Helpers behind the scanner API.
 *
 *  These functions run before requalification: they surface the raw,
 *  specific error types of the lexer, reader, alias and history
 *  submodules. Every public endpoint passes their result through
 *  @ref scanner_error_qualify so only fully qualified errors (plus the
 *  deliberate @c ERR_VEOF exception) cross the scanner API.
 */

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup scanner_priv
 * @brief Expands a word token's alias and re-lexes from the expansion.
 *
 * When @p token expands, pushes the expansion as a new input on the lexer
 * stack and re-runs the lexer so the next token comes from the expanded
 * text; otherwise leaves @p token unchanged.
 *
 * @param scanner Scanner state (borrowed).
 * @param token Word token to expand and replace (borrowed).
 * @return @c ERR_LIBC on allocation failure, @c ERR_SHELL_NOT_FOUND if the
 *         alias or shell data is unavailable, or a raw lexer error from the
 *         re-lex: @c ERR_VEOF (end of input at a continuation prompt),
 *         @c ERR_UNEXPECTED_EOI, @c ERR_CTX_END_NOT_FOUND,
 *         @c ERR_NO_INPUT_TO_LEX, @c ERR_EMPTY_STACK,
 *         @c ERR_INCOHERENT_STATE, @c ERR_NOT_IMPLEMENTED; @c ERR_NO on
 *         success.
 */
t_error		scanner_alias_expand(t_scanner *scanner, t_token *token);

/**
 * @ingroup scanner_priv
 * @brief Requalifies an error escaping the scanner API.
 *
 * Prints the specific diagnostic at the moment precision is lost, then
 * requalifies: an unexpected end of input during tokenization
 * (@c ERR_VEOF, @c ERR_UNEXPECTED_EOI, @c ERR_CTX_END_NOT_FOUND,
 * @c ERR_NO_DELIM, @c ERR_REDIRECTION)
 * becomes @c ERR_POSIX_SYNTAX, any other unqualified error becomes
 * @c ERR_INTERNAL. @c ERR_LIBC is printed with the scanner context and
 * kept, fully qualified errors (>= @c ERR_INTERRUPTED) pass through
 * untouched.
 *
 * @c ERR_VEOF crosses the API untouched (and unprinted) when @p allow_veof
 * is set: end of input at a point where the exit decision belongs to the
 * caller. When @p allow_veof is false, @c ERR_VEOF means the input ended
 * in the middle of a construct and is requalified as @c ERR_POSIX_SYNTAX.
 *
 * @param err Error to requalify.
 * @param allow_veof Let @c ERR_VEOF cross the API untouched.
 * @return The requalified (and printed) error.
 */
t_error			scanner_error_qualify(t_error err, bool allow_veof);

t_lexer_rules	scanner_lexer_rules();

/**
 * @ingroup scanner_priv
 * @brief Reads the next chunk of input and pushes it on the lexer stack.
 *
 * Allocates an input item and fills it according to the mode (whole file,
 * duplicated command string, whole standard input, or one prompted line),
 * then pushes it. On error, or when the input holds no command (less than
 * two characters), the item is freed and not pushed. Called only when the
 * input stack is empty.
 *
 * @param scanner Scanner state (borrowed).
 * @return @c ERR_LIBC on allocation failure; @c ERR_VEOF at the top-level
 *         end of input of an interactive shell; @c ERR_POSIX_CMD_NOT_FOUND
 *         / @c ERR_POSIX_CMD_NOT_EXECUTABLE (printed) when the script file
 *         cannot be opened; @c ERR_POSIX_READ (printed) on an
 *         unrecoverable read error; @c ERR_INTERRUPTED when a signal
 *         interrupts a file operation; @c ERR_SHELL_NOT_FOUND if the shell
 *         data is unavailable; @c ERR_NO on success.
 */
t_error		scanner_read_input(t_scanner *scanner);

/**
 * @ingroup scanner_priv
 * @brief Builds the body-read arguments from the scanner state: the top
 *        lexer input and its cursor (@c NULL when no input is loaded),
 *        the mode from @p strip and the terminal flag from the input
 *        mode.
 *
 * @param scanner Already initialized scanner state (borrowed).
 * @param out Arguments filled by the function (borrowed).
 * @param strip Tab-stripping mode of the @c <<- operator.
 * @param delim Quote-removed delimiter with its trailing newline
 *              (borrowed, read-only).
 */
void		prepare_heredoc_read_args(
				t_scanner *scanner,
				t_heredoc_read_args *out,
				bool strip,
				const t_string *delim);

t_error		scan_mode_set(t_scan_mode *mode);

t_error		scanner_lexer_continuation(t_lexer *lexer);

#endif
