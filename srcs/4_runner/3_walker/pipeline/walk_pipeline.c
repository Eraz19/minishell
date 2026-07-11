#include "walker.h"
#include "walker_priv.h"
#include "posix_helpers.h"
#include "walk_pipeline_priv.h"
#include "shell.h"
#include <unistd.h>
#include <stdlib.h>

static inline void	walk_pipe_child(t_pipe_run *run)
{
	t_runner		*runner;
	t_ast_command	*command;
	int				exit_status;
	t_error			err;

	err = error(ERR_NO);
	err = shell_init_subshell(SUBSHELL_NORMAL);
	if (err.type == ERR_NO && run->cmd_fds[READ_ID] >= 0)
		err = posix_dup2(run->cmd_fds[READ_ID], STDIN_FILENO);
	if (err.type == ERR_NO && run->cmd_fds[WRITE_ID] >= 0)
		err = posix_dup2(run->cmd_fds[WRITE_ID], STDOUT_FILENO);
	command = &((t_ast_command *)run->pipeline->commands.data)[run->command_id];
	runner = run->runner;
	walk_pipe_free(run);
	if (err.type == ERR_NO)
		err = walk_command(runner, command, &exit_status);
	if (err.type)
		exit((int)err.type);
	exit(exit_status);
}

static inline t_error	walk_pipe_one_command(t_pipe_run *run, int *exit_status)
{
	pid_t	child_pid;
	t_error	err;

	child_pid = fork();
	if (child_pid < 0)
	{
		err = error_sys();
		*exit_status = (int)err.type;
		return (err);
	}
	else if (child_pid == 0)
		walk_pipe_child(run);
	run->pids[run->command_id] = child_pid;
	run->command_id++;
	err = walk_pipe_close_fd(run, run->cmd_fds[READ_ID]);
	if (err.type == ERR_NO)
		err = walk_pipe_close_fd(run, run->pipe_fds[WRITE_ID]);
	if (err.type)
		*exit_status = (int)err.type;
	return (err);
}

t_error	walk_pipeline(
			t_runner *runner,
			t_ast_pipeline *pipeline,
			int *exit_status)
{
	t_pipe_run	run;
	t_error		err;
	t_error		err_cleanup;

	*exit_status = -1;
	if (pipeline->commands.len == 1)
		return (walk_pipe_single_command(runner, pipeline, exit_status));
	err = walk_pipe_spawn(runner, pipeline, &run);
	if (err.type)
		return (walk_normalize_output(err, NULL, exit_status));
	while (run.command_id < pipeline->commands.len)
	{
		err = walk_pipe_next_pipe(&run);
		if (err.type)
			*exit_status = (int)err.type;
		if (err.type == ERR_NO)
			err = walk_pipe_one_command(&run, exit_status);
		if (err.type)
			break ;
	}
	err_cleanup = walk_pipe_finalize(&run);
	*exit_status = run.exit_status;
	walk_pipe_free(&run);
	return (walk_normalize_output(err, &err_cleanup, exit_status));
}
