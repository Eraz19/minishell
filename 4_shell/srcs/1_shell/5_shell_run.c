#include "shell_priv.h"
#include "runner.h"
#include <stdlib.h>
#include "sig.h"

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

static inline t_error	shell_prepare(t_shell_loading_options *options)
{
	t_shell	*shell;

	assert(options->argc > 0);
	assert(options->argv != NULL);
	assert(options->envp != NULL);
	options->shell = malloc(sizeof(*shell));
	if (!options->shell)
		return (error_print(error_sys(),
					"unable to malloc shell data struct", NULL, NULL));
	shell_init(options->shell);
	shell_set(options->shell);
	print_pass("shell initialized\n");
	return (shell_load(options));
}

static inline t_scan_mode	shell_resolve_scan_mode(t_shell *shell)
{
	if (option_is_active_in(shell->params.options, OPT_STDIN_INPUT))
		return (SCAN_MODE_STDIN);
	else if (option_is_active_in(shell->params.options, OPT_CMD_STRING))
		return (SCAN_MODE_STRING);
	else
		return (SCAN_MODE_FILE);
}

static inline int	shell_exec(t_shell *shell)
{
	t_scan_mode	mode;
	t_runner	*runner;
	t_error		err;

	mode = shell_resolve_scan_mode(shell);
	err = shell_get_new_runner(&runner, mode, NULL);
	if (err.type)
	{
		(void)error_print(err, NULL, NULL);
		return ((int)err.type);
	}
	(void)runner_run(runner);
	sig_process_exit();
	shell_destroy_last_instance();
	err = history_save();
	if (err.type)
		(void)error_print(err, "history", NULL, NULL);
	return (env_get_last_status_from(&shell->params));
}

int	shell_run(int argc, char **argv, char **envp, bool build_parser_tables)
{
	t_shell_loading_options	options;
	int						exit_status;
	t_error					err;

	shell_start_logs();
	options.argc = argc;
	options.argv = argv;
	options.envp = envp;
	options.build_parser_tables = build_parser_tables;
	err = shell_prepare(&options);
	if (err.type)
		exit_status = (int)err.type;
	else
	{
		err = shell_exec_env();
		if (err.type)
			exit_status = (int)err.type;
		else
			exit_status = shell_exec(options.shell);
	}
	shell_free(options.shell);
	shell_stop_logs();
	return (exit_status);
}
