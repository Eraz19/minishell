#include "shell_priv.h"
#include <stdlib.h>

/* -------------------- DEBUG (START) -------------------- */
# include <locale.h>	// DEBUG
# include "logs.h"		// DEBUG
# include <assert.h>	// DEBUG

static inline void	shell_start_logs(void)
{
	setlocale(LC_NUMERIC, "de_DE");
#ifdef DEBUG_LOGS
	print_start(99, "shell_run()");
#endif
}

static inline void	shell_stop_logs(void)
{
#ifdef DEBUG_LOGS
	print_stop();
#endif
	setlocale(LC_NUMERIC, "");	// DEBUG
}

/* -------------------- DEBUG (STOP) -------------------- */

t_error	shell_prepare(int argc, char **argv, char **envp, t_shell **out_shell)
{
	t_shell	*shell;

	assert(argc > 0);
	assert(argv != NULL);
	assert(envp != NULL);
	shell = malloc(sizeof(*shell));
	if (!shell)
		return (error_print(error_sys(),
					"unable to malloc shell data struct", NULL, NULL));
	shell_init(shell);
	shell_set(shell);
	*out_shell = shell;
	print_pass("shell initialized\n");
	return (shell_load(shell, argc, argv, envp));
}

int	shell_run(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	t_error	err;

	shell_start_logs();
	err = shell_prepare(argc, argv, envp, &shell);
	if (err.type == ERR_NO)
		err = shell_exec_env();
	if (err.type == ERR_NO)
		err = runner_run(&shell->runner);
	if (err.type)
		(void)history_save();
	else
		err = history_save();
	if (err.type)
		err = error_print(err, "history", NULL, NULL);
	shell_free(shell);
	shell_stop_logs();
	return ((int)err.type);
}
