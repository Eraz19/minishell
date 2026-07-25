#include "shell.h"
#include "posix_helpers.h"
#include <fcntl.h>
#include <unistd.h>

// @ret ERR_NO / ERR_INTERNAL
t_error	shell_is_subshell(bool *out)
{
	t_shell	*shell;

	shell = shell_get();
	if (shell == NULL)
		return (error_print(error(ERR_INTERNAL),
					"shell not found", NULL, NULL));
	*out = shell->is_subshell;
	return (error(ERR_NO));
}

// @ret ERR_INVALID_USAGE / ERR_LIBC
static inline t_error	shell_set_stdin_to_dev_null(void)
{
	int		dev_null_fd;
	int		oflags;
	t_error	err;

	oflags = O_RDONLY;
	err = posix_open("/dev/null", oflags, &dev_null_fd);
	if (err.type)
		return (error_print(err, "subshell initialization failed",
				"unable to open /dev/null", NULL, NULL));
	if (dev_null_fd == STDIN_FILENO)
		return (err);
	err = posix_dup2(dev_null_fd, STDIN_FILENO);
	if (err.type)
		(void)posix_close_if_open(dev_null_fd);
	else
		err = posix_close_if_open(dev_null_fd);
	return (err);
}

t_error	shell_init_subshell(t_subshell_mode mode)
{
	t_shell	*shell;
	bool	job_control;
	t_error	err;

	shell = shell_get();
	if (shell == NULL)
		return (error_print(error(ERR_INTERNAL),
					__func__, "shell not found", NULL, NULL));
	job_control = option_is_active_in(shell->params.options, OPT_MONITOR);
	shell->is_subshell = true;
	params_init_subshell(&shell->params, mode == SUBSHELL_ASYNC_AND_OR && !job_control);
	if (mode == SUBSHELL_ASYNC_AND_OR && !job_control)
	{
		err = shell_set_stdin_to_dev_null();
		if (err.type)
		{
			err = error_print(err, "subshell initialization failed", NULL, NULL);
			if (err.type == ERR_INVALID_USAGE)
				err.type = ERR_INTERNAL;
			return (err);
		}
	}
	return (error(ERR_NO));
}
