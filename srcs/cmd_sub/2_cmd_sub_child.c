#include "cmd_sub_priv.h"
#include "posix_helpers.h"
#include "runner.h"
#include "walker.h"
#include <stdlib.h>
#include <unistd.h>

static inline void	cmd_sub_child_dup_and_close(int pipe_fds[2])
{
	t_error	err;

	err = posix_close_if_open(pipe_fds[0]);
	if (err.type)
		exit((int)error_priorize(err, posix_close_if_open(pipe_fds[1])).type);
	if (pipe_fds[1] == STDOUT_FILENO)
		return ;
	err = posix_dup2(pipe_fds[1], STDOUT_FILENO);
	err = error_priorize(err, posix_close_if_open(pipe_fds[1]));
	if (err.type)
		exit((int)err.type);
}

static inline void	cmd_sub_child_init_subshell_string(
						const t_string *cmd_string,
						t_shell *shell)
{
	t_error	err;

	err = shell_init_subshell(SUBSHELL_NORMAL);
	if (err.type)
		exit((int)err.type);
	err = scanner_set_cmd_sub_input(cmd_string);
	if (err.type)
		exit((int)err.type);
	builder_clear(&shell->builder);
}

void	cmd_sub_child_string(const t_string *cmd_string, int pipe_fds[2])
{
	t_shell	*shell;
	t_error	err;

	cmd_sub_child_dup_and_close(pipe_fds);
	shell = shell_get();
	if (shell == NULL)
	{
		err = error(ERR_INTERNAL);
		(void)error_print(err, "cmd sub child", "shell not found", NULL, NULL);
		exit((int)err.type);
	}
	cmd_sub_child_init_subshell_string(cmd_string, shell);
	runner_run(shell);
	exit(params_get_last_status_from(&shell->params));
}

void	cmd_sub_child_ast(t_ast_root *ast_root, int pipe_fds[2])
{
	t_shell	*shell;
	t_error	err;

	cmd_sub_child_dup_and_close(pipe_fds);
	shell = shell_get();
	if (shell == NULL)
	{
		err = error(ERR_INTERNAL);
		(void)error_print(err, "cmd sub child", "shell not found", NULL, NULL);
		exit((int)err.type);
	}
	err = shell_init_subshell(SUBSHELL_NORMAL);
	if (err.type)
		exit((int)err.type);
	walk(&shell->runner, ast_root);
	exit(params_get_last_status_from(&shell->params));
}
