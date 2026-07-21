#include "cmd_sub_priv.h"
#include "posix_helpers.h"
#include "runner.h"
#include "shell.h"
#include <stdlib.h>
#include <unistd.h>

#define CMD_SUB_PREFIX	"cmd sub child"
#define SHELL_NF		"shell not found"

static inline void	cmd_sub_child_dup_and_close(int pipe_fds[2])
{
	t_error	err;

	err = posix_close_if_open(pipe_fds[0]);
	if (err.type)
	{
		err = error_print(err, CMD_SUB_PREFIX, NULL, NULL);
		err = error_priorize(err, posix_close_if_open(pipe_fds[1]));
		exit((int)err.type);
	}
	if (pipe_fds[1] == STDOUT_FILENO)
		return ;
	err = posix_dup2(pipe_fds[1], STDOUT_FILENO);
	if (err.type)
	{
		err = error_print(err, CMD_SUB_PREFIX, NULL, NULL);
		err = error_priorize(err, posix_close_if_open(pipe_fds[1]));
		exit((int)err.type);
	}
	err = posix_close_if_open(pipe_fds[1]);
	if (err.type)
		exit((int)error_print(err, CMD_SUB_PREFIX, NULL, NULL).type);
}

void	cmd_sub_child_string(const t_string *cmd_string, int pipe_fds[2])
{
	t_runner	runner;
	int			exit_status;
	t_error		err;

	cmd_sub_child_dup_and_close(pipe_fds);
	err = runner_init(&runner, SCAN_MODE_STRING);
	if (err.type)
		exit((int)error_print(err, CMD_SUB_PREFIX, NULL, NULL).type);
	err = shell_init_subshell(SUBSHELL_NORMAL, &runner.parser.scanner);
	if (err.type)
		exit((int)error_print(err, CMD_SUB_PREFIX, NULL, NULL).type);
	scanner_set_input(&runner.parser.scanner, cmd_string);
	runner_run(&runner);
	runner_free(&runner);
	err = params_get_last_status(&exit_status);
	if (err.type)
		exit((int)error_print(err, CMD_SUB_PREFIX, NULL, NULL).type);
	exit(exit_status);
}

void	cmd_sub_child_ast(t_ast_root *ast_root, int pipe_fds[2])
{
	t_runner	runner;
	int			exit_status;
	t_error		err;

	cmd_sub_child_dup_and_close(pipe_fds);
	err = runner_init(&runner, SCAN_MODE_STRING);
	if (err.type)
		exit((int)error_print(err, CMD_SUB_PREFIX, NULL, NULL).type);
	err = shell_init_subshell(SUBSHELL_NORMAL, &runner.parser.scanner);
	if (err.type)
		exit((int)error_print(err, CMD_SUB_PREFIX, NULL, NULL).type);
	runner_run_ast(&runner, ast_root);
	runner_free(&runner);
	err = params_get_last_status(&exit_status);
	if (err.type)
		exit((int)error_print(err, CMD_SUB_PREFIX, NULL, NULL).type);
	exit(exit_status);
}
