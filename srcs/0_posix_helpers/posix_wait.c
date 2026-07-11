#include "error.h"
#include "shell.h"
#include <errno.h>
#include <sys/wait.h>

t_error	posix_wait(pid_t pid, int *exit_status)
{
	int		status;
	t_error	err;

	*exit_status = -1;
	err = error(ERR_NO);
	while (waitpid(pid, &status, 0) == -1)
	{
		if (errno == EINTR)
		{
			err = error_priorize(err, shell_should_interrupt());
			continue ;
		}
		return (error_sys());
	}
	if (WIFEXITED(status))
		*exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		*exit_status = ERR_POSIX_SIGNAL_BASE_CODE + WTERMSIG(status);
	return (err);
}
