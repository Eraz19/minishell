/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_shell_run.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:56:56 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 20:49:24 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_priv.h"
#include "runner.h"
#include <stdlib.h>
#include "sig.h"

static inline t_error	shell_load_runner(t_shell *shell, t_runner **runner)
{
	const char	*input;

	if (option_is_active_in(shell->params.options, OPT_STDIN_INPUT))
		return (shell_get_new_runner(runner, SCAN_MODE_STDIN, NULL));
	input = shell->params.specials.source.data;
	if (option_is_active_in(shell->params.options, OPT_CMD_STRING))
		return (shell_get_new_runner(runner, SCAN_MODE_STRING, input));
	else
		return (shell_get_new_runner(runner, SCAN_MODE_FILE, input));
}

static inline int	shell_exec(t_shell *shell)
{
	t_runner	*runner;
	t_error		err;

	err = shell_load_runner(shell, &runner);
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

int	shell_run(int argc, char **argv, char **envp, bool must_init)
{
	t_shell_loading_options	options;
	int						exit_status;
	t_error					err;

	options.shell = shell_get();
	options.argc = argc;
	options.argv = argv;
	options.envp = envp;
	if (must_init == true)
		shell_init(options.shell);
	err = shell_load(options.shell, options.argc, options.argv, options.envp);
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
	return (exit_status);
}
