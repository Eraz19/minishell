#include "error.h"
#include <errno.h>
#include <sys/wait.h>

t_error	walk_wait(pid_t pid, int *exit_status)
{
	int		status;

	*exit_status = -1;
	while (waitpid(pid, &status, 0) == -1)
	{
		if (errno == EINTR)
			continue ;
		return (error_sys());
	}
	if (WIFEXITED(status))
		*exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		*exit_status = ERR_POSIX_SIGNAL_BASE_CODE + WTERMSIG(status);
	return (error(ERR_NO));
}
