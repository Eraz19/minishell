#include "cmd_sub.h"
#include "cmd_sub_priv.h"
#include "posix_helpers.h"
#include <unistd.h>

t_error	cmd_sub_run(
			const t_string *cmd_string,
			t_string *out_string,
			int *out_exit_status)
{
	int		pipe_fds[2];
	pid_t	pid;
	t_error	err;

	if (pipe(pipe_fds) == -1)
		return (error_sys());
	pid = fork();
	if (pid < 0)
	{
		err = error_sys();
		err = error_priorize(err, posix_close_if_open(pipe_fds[0]));
		return (error_priorize(err, posix_close_if_open(pipe_fds[1])));
	}
	else if (pid == 0)
		cmd_sub_child(cmd_string, pipe_fds);
	return (cmd_sub_parent(pipe_fds, pid, out_string, out_exit_status));
}
