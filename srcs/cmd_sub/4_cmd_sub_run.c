#include "cmd_sub.h"
#include "cmd_sub_priv.h"
#include "posix_helpers.h"
#include <unistd.h>

t_error	cmd_sub_run_ast(
			t_ast_vector *ast_vector,
			size_t index,
			t_string *out_string,
			int *out_exit_status)
{
	t_ast_root	*ast_root;
	int			pipe_fds[2];
	pid_t		pid;
	t_error		err;

	(void)string_init(out_string, 0, NULL, 0);
	err = ast_vector_get(ast_vector, index, &ast_root);
	if (err.type)
		return (err);
	if (pipe(pipe_fds) == -1)
		return (error_sys());
	pid = fork();
	if (pid < 0)
	{
		err = error_sys();
		err = error_priorize(err, posix_close_if_open(pipe_fds[0]));
		return (error_priorize(err, posix_close_if_open(pipe_fds[1])));
	}
	else if (pid == 0)
		cmd_sub_child_ast(ast_root, pipe_fds);
	return (cmd_sub_parent(pipe_fds, pid, out_string, out_exit_status));
}

t_error	cmd_sub_run_string(
			const t_string *cmd_string,
			t_string *out_string,
			int *out_exit_status)
{
	int		pipe_fds[2];
	pid_t	pid;
	t_error	err;

	(void)string_init(out_string, 0, NULL, 0);
	if (pipe(pipe_fds) == -1)
		return (error_sys());
	pid = fork();
	if (pid < 0)
	{
		err = error_sys();
		err = error_priorize(err, posix_close_if_open(pipe_fds[0]));
		return (error_priorize(err, posix_close_if_open(pipe_fds[1])));
	}
	else if (pid == 0)
		cmd_sub_child_string(cmd_string, pipe_fds);
	return (cmd_sub_parent(pipe_fds, pid, out_string, out_exit_status));
}
