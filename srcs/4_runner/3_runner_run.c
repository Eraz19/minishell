#include "error.h"
#include "builder.h"
#include "runner.h"
#include "runner_priv.h"
#include "walker.h"
#include "params.h"
#include "shell.h"
#include <stdbool.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <unistd.h>
# include "logs.h"	// DEBUG

// ERR_NO / ERR_LIBC
static inline t_error	runner_set_stdin_to_blocking(void)
{
	int			enabled;
	struct stat	stat_buff;
	bool		is_a_terminal;
	bool		is_fifo;
	
	is_a_terminal = isatty(STDIN_FILENO);
	if (!is_a_terminal)
	{
		if (fstat(STDIN_FILENO, &stat_buff) != 0)
			return (error_print(error_sys(),
					"unable to check if stdin is FIFO", NULL, NULL));
		is_fifo = S_ISFIFO(stat_buff.st_mode);
		if (!is_fifo)
		{
			print_pass("stdin is not a fifo: not set to blocking mode\n");
			return (error(ERR_NO));
		}
	}
	enabled = 0;
	if (ioctl(STDIN_FILENO, FIONBIO, &enabled) == -1)
		return (error_print(error_sys(),
				"Unable to set stdin to blocking mode", NULL, NULL));
	print_pass("stdin has been set to blocking mode\n");
	return (error(ERR_NO));
}

/*
Non-fatal errors should be handled in walkers.
Therefore, only fatal errors should bubble up to the main loop.
*/
t_error	runner_run(t_shell *shell)
{
	t_ast_root	ast_root;
	int			exit_status;
	t_error		err;

	err = error(ERR_NO);
	while (err.type == ERR_NO)
	{
		ast_root_init(&ast_root);
		runner_set_stdin_to_blocking();
		err = builder_get_ast(&ast_root);
		if (err.type == ERR_NO)
			err = walk(&shell->runner, &ast_root, &exit_status);
		err = error_priorize(err, params_reap(&shell->params));
		runner_handle_errors(shell, &err);
		ast_root_free(&ast_root);
	}
	return (err);
}
