#include "runner.h"
#include "shell.h"
#include "cmd_dispatcher_priv.h"
#include "redirector.h"
#include "posix_helpers.h"
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>

static inline int	cmd_exec_in_shell(t_cmd *cmd)
{
	const char	*shell_name;
	char		**cmd_name;
	int			argc;
	t_error		err;

	shell_name = shell_get_name();
	if (!vector_insert(&cmd->argv, 0, &shell_name))
	{
		err = error_print(error_sys(), "runner", "executor",
				"unable to edit argv in execve fallback", NULL, NULL);
		return ((int)err.type);	
	}
	cmd_name = &((char **)cmd->argv.data)[1];
	free(*cmd_name);
	*cmd_name = cmd->path.data;
	cmd->path.cap = 0;
	argc = (int)cmd->argv.len - 1;
	shell_free_void();
	return (shell_run(argc, cmd->argv.data, cmd->envp.data));
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
	if (exit_status == (int)ERR_POSIX_CMD_NOT_FOUND
		|| exit_status == (int)ERR_POSIX_CMD_NOT_EXECUTABLE)
		(void)error_print(
			error((t_error_type)exit_status),
			"runner",
			"executor",
			cmd->name.data,
			NULL,
			NULL);
	shell_free_void();
	exit(exit_status);
}

t_error	cmd_exec_external(t_cmd *cmd, t_runner *runner, int *exit_status)
{
	pid_t	pid;
	t_error	err;

	pid = fork();
	if (pid < 0)
		return (error_sys());
	else if (pid == 0)
		cmd_exec_child(cmd, runner);
	err = posix_wait(pid, exit_status);
	cmd->exit_status = *exit_status;
	return (err);
}
