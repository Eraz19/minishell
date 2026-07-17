#ifndef CMD_SUB
# define CMD_SUB

# include "error.h"
# include "libft.h"
# include "ast.h"
# include <stddef.h>

// @warning ast_vector must have been initialized before calling this function
t_error	cmd_sub_find_end(ssize_t *out_closing_token_id, t_ast_vector *ast_vector);
t_error	cmd_sub_run_string(
			const t_string *cmd_string,
			t_string *out_string,
			int *out_exit_status);
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
