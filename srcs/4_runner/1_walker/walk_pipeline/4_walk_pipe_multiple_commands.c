#include "walker.h"
#include "posix_helpers.h"
#include "walk_pipeline_priv.h"
#include "shell.h"
#include <unistd.h>
#include <stdlib.h>

static inline void	walk_pipe_child(t_pipe_run *run)
{
	t_ast_command	*command;
	int				exit_status;
	t_error			err;

	err = error(ERR_NO);
	exit_status = -1;
	err = shell_init_subshell(SUBSHELL_NORMAL);
	if (err.type == ERR_NO && run->cmd_fds[READ_ID] >= 0)
		err = posix_dup2(run->cmd_fds[READ_ID], STDIN_FILENO);
	if (err.type == ERR_NO && run->cmd_fds[WRITE_ID] >= 0)
		err = posix_dup2(run->cmd_fds[WRITE_ID], STDOUT_FILENO);
	command = &((t_ast_command *)run->pipeline->commands.data)[run->command_id];
	walk_pipe_free(run);
	if (err.type == ERR_NO)
		err = walk_command(run->runner, command, &exit_status);
	shell_free_void();
	exit(exit_status);
}

static inline t_error	walk_pipe_one_command(t_pipe_run *run)
{
	pid_t	child_pid;
	t_error	err;

	child_pid = fork();
	if (child_pid < 0)
		return (error_sys());
	else if (child_pid == 0)
		walk_pipe_child(run);
	run->pids[run->command_id] = child_pid;
	run->command_id++;
	err = walk_pipe_close_fd(run, run->cmd_fds[READ_ID]);
	if (err.type == ERR_NO)
		err = walk_pipe_close_fd(run, run->pipe_fds[WRITE_ID]);
	return (err);
}

t_error	walk_pipe_multiple_commands(
							t_runner *runner,
							t_ast_pipeline *pipeline,
							int *exit_status)
{
	t_pipe_run	run;
	t_error		err;

	err = walk_pipe_spawn(runner, pipeline, &run);
	if (err.type)
		return (err);
	while (run.command_id < pipeline->commands.len)
	{
		err = walk_pipe_next_pipe(&run);
		if (err.type == ERR_NO)
			err = walk_pipe_one_command(&run);
		if (err.type)
			break ;
	}
	err = error_priorize(err, walk_pipe_finalize(&run));
	*exit_status = run.exit_status;
	walk_pipe_free(&run);
	return (err);
}
