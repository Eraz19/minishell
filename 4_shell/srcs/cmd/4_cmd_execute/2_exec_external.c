#include "cmd.h"
#include "shell.h"
#include "posix_helpers.h"
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>
#include <assert.h>	// DEBUG
#ifdef DEBUG_CMD
# include "logs.h"	// DEBUG
#endif

#define FALLBACK_ERR	"unable to edit argv in execve fallback"

static inline t_error	cmd_exec_add_shell_name_to_argv(t_vector *argv)
{
	char	*shell_name;
	t_error	err;

	shell_name = str_dup(shell_get_name());
	if (shell_name == NULL)
		return (err = error_print(error_sys(), FALLBACK_ERR, NULL, NULL));
	else if (!vector_insert(argv, 0, &shell_name))
	{
		err = error_print(error_sys(), FALLBACK_ERR, NULL, NULL);
		free(shell_name);
		return (err);
	}
	return (error(ERR_NO));
}

static inline void	cmd_exec_fallback(t_cmd *cmd, int *exit_status)
{
	char		**cmd_name;
	int			argc;
	t_shell		*shell;
	t_error		err;

	err = cmd_exec_add_shell_name_to_argv(&cmd->argv);
	if (err.type)
	{
		*exit_status = (int)err.type;
		return ;
	}
	cmd_name = &((char **)cmd->argv.data)[1];
	free(*cmd_name);
	*cmd_name = cmd->entry.data.cmd_path.data;
	cmd->entry.data.cmd_path.cap = 0;
	argc = (int)cmd->argv.len - 1;
	shell_init_subshell(SUBSHELL_NORMAL);
	shell_clear();
	shell = shell_get();
	assert(shell != NULL);
	history_free(&shell->history);
	*exit_status = shell_run(argc, cmd->argv.data, cmd->envp.data, false);
}

static inline void	cmd_exec_child(t_cmd *cmd)
{
	int		exit_status;
	t_error	err;

	(void)execve(cmd->entry.data.cmd_path.data, cmd->argv.data, cmd->envp.data);
	if (errno == ENOEXEC)
		cmd_exec_fallback(cmd, &exit_status);
	else
	{
		if (errno == ENOENT || errno == ENOTDIR)
			err = error(ERR_POSIX_CMD_NOT_FOUND);
		else
			err = error(ERR_POSIX_CMD_NOT_EXECUTABLE);
		(void)error_print(err, cmd->name.data, NULL, NULL);
		exit_status = (int)err.type;
	}
	cmd_free(cmd);
	shell_free_void();
	exit(exit_status);
}

t_error	exec_external(t_cmd *cmd, int *exit_status)
{
	pid_t	pid;

#ifdef DEBUG_CMD
	fprintf(stderr, MAGENTA "############## EXTERNAL %s (START) ##############\n" NC, cmd->name.data);
#endif
	pid = fork();
	if (pid < 0)
		return (error_sys());
	else if (pid == 0)
		cmd_exec_child(cmd);
	return (posix_wait_and_retry(pid, exit_status));
}
