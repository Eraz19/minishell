#include "error.h"
#include "shell.h"
#include <errno.h>
#include <sys/wait.h>

static inline void	parse_status(pid_t ret, int *status)
{
	if (ret <= 0)
		return ;
	else if (WIFEXITED(*status))
		*status = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
		*status = ERR_POSIX_SIGNAL_BASE_CODE + WTERMSIG(*status);
}

static inline t_error	posix_wait_(pid_t pid, int options, int *status)
{
	pid_t	ret;
	t_error	err;

	*status = -1;
	err = error(ERR_NO);
	while (true)
	{
		ret = waitpid(pid, status, options);
		if (ret < 0)
		{
			if (errno == EINTR)
			{
				err = error_priorize(err, shell_should_interrupt());
				continue ;
			}
			return (error_sys());
		}
		break ;
	}
	parse_status(ret, status);
	return (err);
}

t_error	posix_wait(pid_t pid, int *exit_status)
{
	return (posix_wait_(pid, 0, exit_status));
}

t_error	posix_wait_with_options(pid_t pid, int options, int *exit_status)
{
	return (posix_wait_(pid, options, exit_status));
}
