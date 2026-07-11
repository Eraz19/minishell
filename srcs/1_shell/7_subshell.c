#include "shell.h"
#include "posix_helpers.h"
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
# include "logs.h"

// TODO
static inline t_error	shell_reset_unignored_traps(t_shell *shell, t_subshell_mode mode)
{
	if (mode == SUBSHELL_CMD_SUB_TRAP_ONLY)
		return (error(ERR_NO));
	print_warn("%s() not implemented yet => skipping.\n", __func__);
	(void)shell;
	return (error(ERR_NO));
}

// @ret ERR_INVALID_USAGE / ERR_INTERRUPTED / ERR_LIBC
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

// @ret ERR_LIBC
static inline t_error	shell_ignore_signal(int signo)
{
	struct sigaction	action;

	action.sa_handler = SIG_IGN;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	if (sigaction(signo, &action, NULL) == -1)
		return (error_sys());
	return (error(ERR_NO));
}

// @ret ERR_INVALID_USAGE / ERR_INTERRUPTED / ERR_LIBC
static inline t_error	shell_handle_async_and_or(t_shell *shell, t_subshell_mode mode)
{
	t_error	err;

	if (mode != SUBSHELL_ASYNC_AND_OR)
		return (error(ERR_NO));
	if (option_is_active_in(shell->params.options, OPT_MONITOR) == true)
		return (error(ERR_NO));
	err = shell_set_stdin_to_dev_null();
	if (err.type == ERR_NO)
		err = shell_ignore_signal(SIGINT);
	if (err.type == ERR_NO)
		err = shell_ignore_signal(SIGQUIT);
	return (err);
}

t_error	shell_init_subshell(t_subshell_mode mode)
{
	t_shell	*shell;
	t_error	err;

	shell = shell_get();
	if (shell == NULL)
		err = error(ERR_SHELL_NOT_FOUND);
	if (err.type == ERR_NO)
		err = shell_reset_unignored_traps(shell, mode);
	if (err.type == ERR_NO)
	{
		option_set(&shell->params.options, OPT_INTERACTIVE, false);
		err = shell_handle_async_and_or(shell, mode);
	}
	if (err.type)
	{
		err = error_print(err, "subshell initialization failed", NULL, NULL);
		if (err.type == ERR_INVALID_USAGE)
			err.type = ERR_INTERNAL;
	}
	return (err);
}
