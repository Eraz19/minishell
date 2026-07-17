#ifndef CMD_SUB
# define CMD_SUB

# include "error.h"
# include "libft.h"
# include "ast.h"
# include <stddef.h>

/** @defgroup cmd_sub Command substitution API
 *  @brief Locates and executes @c $(...) command substitutions
 *         (POSIX 2.6.3).
 *
 *  The closing parenthesis is found by recursive parsing: a scanner
 *  and builder clone re-reads the main scanner's input until the
 *  unbalanced @c ')' reduce hook fires (@ref cmd_sub_find_end).
 *  Execution runs the substitution text in a forked subshell and
 *  captures its standard output through a pipe
 *  (@ref cmd_sub_run_string).
 */

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup cmd_sub
 * @brief Finds the closing parenthesis of the @c $( being tokenized by
 *        recursive parsing (POSIX 2.6.3) on a scanner and builder
 *        clone; the main scanner's input is not consumed.
 *
 * @warning The builder does not requalify the parse errors: besides the
 *          qualified types below, raw parser diagnostics
 *          (@c ERR_PARSER_EMPTY_GOTO (printed), @c ERR_EOF) and the
 *          scanner's @c ERR_VEOF exception can cross this API.
 * @param out_token_id Set to the closing parenthesis token's end offset
 *                     in the scanned input (borrowed).
 * @return @c ERR_INTERNAL (printed) if the shell data is unavailable;
 *         @c ERR_LIBC (printed) on allocation failure;
 *         @c ERR_POSIX_SYNTAX (printed) when the substitution does not
 *         parse or the input ends before the closing parenthesis;
 *         @c ERR_POSIX_READ, @c ERR_POSIX_CMD_NOT_FOUND,
 *         @c ERR_POSIX_CMD_NOT_EXECUTABLE (printed) or
 *         @c ERR_INTERRUPTED from the input reads; @c ERR_NO on
 *         success.
 */
t_error	cmd_sub_find_end(ssize_t *out_token_id);

/**
 * @ingroup cmd_sub
 * @brief Runs an already built syntax tree as a command substitution.
 *
 * @warning Declared but NOT IMPLEMENTED: no definition exists in the
 *          tree, linking a call fails (TODO: implement or remove).
 * @param ast_root Tree to run (borrowed).
 * @param out_string String receiving the captured output (borrowed).
 * @param out_exit_status Set to the substitution's exit status
 *                        (borrowed).
 */
t_error	cmd_sub_run_ast(
			t_ast_root *ast_root,
			t_string *out_string,
			int *out_exit_status);

/**
 * @ingroup cmd_sub
 * @brief Runs @p cmd_string in a forked subshell and captures its
 *        standard output: pipes, forks (the child re-enters the runner
 *        and exits with its last command's status), reads the whole
 *        pipe, waits, then trims every trailing newline
 *        (POSIX 2.6.3).
 *
 * @param cmd_string Command text to run (borrowed, read-only).
 * @param out_string Already initialized string the captured output is
 *                   appended to (borrowed).
 * @param out_exit_status Set to the child's wait status (borrowed).
 * @return @c ERR_LIBC if the pipe, fork, read, close or wait fails;
 *         @c ERR_INTERRUPTED when a signal interrupts the wait;
 *         @c ERR_NO on success.
 */
t_error	cmd_sub_run_string(
			const t_string *cmd_string,
			t_string *out_string,
			int *out_exit_status);

#endif
