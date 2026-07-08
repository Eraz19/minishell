#include "runner.h"
#include "shell.h"
#include "cmd_dispatcher_priv.h"
#include "redirector.h"
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>

static inline int	cmd_exec_in_shell(t_cmd *cmd)
{
	/*
	TODO:
		reset lexer / parser
		insert shell_name at args[0]
		insert command at args[1]
		set input mode = cmd_file
		execute
	*/
	(void)cmd;
	return((int)ERR_POSIX_CMD_NOT_EXECUTABLE);
}

static inline void	cmd_exec_child(t_cmd *cmd, t_runner *runner)
{
	int	exit_status;

	redirect_close_backups(&runner->redirector);
	(void)execve(
			cmd->path.data,
			(char *const *)cmd->argv.data,
			(char *const *)cmd->envp.data);
	if (errno == ENOEXEC)
		exit_status = cmd_exec_in_shell(cmd);
	else if (errno == ENOENT || errno == ENOTDIR)
		exit_status = (int)ERR_POSIX_CMD_NOT_FOUND;
	else
		exit_status = (int)ERR_POSIX_CMD_NOT_EXECUTABLE;
	(void)error_print(error((t_error_type)exit_status), "executor", cmd->name.data, NULL, NULL);
	exit(exit_status);
}

static inline t_error	cmd_exec_parent(t_cmd *cmd, pid_t child_pid)
{
	int		status;
	t_error	err;

	while (waitpid(child_pid, &status, 0) == -1)
	{
		if (errno == EINTR)
		{
			(void)err;
			/*
			TODO: implement full signal handling (should kill the child if interrupted)
			err = shell_should_interrupt();
			if (err.type)
			{
				cmd->exit_status = (int)ERR_POSIX_CMD_NOT_EXECUTABLE;
				return (err);
			}
			*/
			continue ;
		}
		return (error_sys());
	}
	if (WIFEXITED(status))
		cmd->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		cmd->exit_status = (int)ERR_POSIX_SIGNAL + WTERMSIG(status);
	return (error(ERR_NO));
}

t_error	cmd_exec_external(t_cmd *cmd, t_runner *runner)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (error_sys());
	else if (pid == 0)
		cmd_exec_child(cmd, runner);
	return (cmd_exec_parent(cmd, pid));
}
