/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_sig_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:14:00 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:14:01 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig.h"
#include "sig_priv.h"
#include "builtins.h"
#include "env.h"
#include <stdlib.h>

// @ret ERR_LIBC
static inline t_error	sig_build_argv(char ***out_argv, const char *cmd)
{
	t_error	err;

	*out_argv = malloc(3 * sizeof(**out_argv));
	if (*out_argv == NULL)
		return (error_sys());
	(*out_argv)[0] = str_dup("eval");
	if ((*out_argv)[0] == NULL)
		return (err = error_sys(), free(*out_argv), err);
	(*out_argv)[1] = str_dup(cmd);
	if ((*out_argv)[1] == NULL)
		return (err = error_sys(), free((*out_argv)[0]), free(*out_argv), err);
	(*out_argv)[2] = NULL;
	return (error(ERR_NO));
}

// TODO: depending on future eval implementation, may return:
// @ret ERR_POSIX_READ / ERR_POSIX_SYNTAX
// 		/ ERR_POSIX_EXPANSION / ERR_POSIX_REDIR_SPECIAL / ERR_POSIX_ASSIGNMENT
// 		/ ERR_POSIX_CMD_NOT_FOUND / ERR_POSIX_CMD_NOT_EXECUTABLE
// 		/ ERR_BUILTIN / ERR_POSIX_BUILTIN_SPECIAL
// 		/ ERR_EXIT / ERR_EXIT_WITH_CURRENT_STATUS
// 		/ ERR_UB / ERR_INTERNAL / ERR_LIBC
static inline t_error	sig_process_cmd(const t_string *cmd, int saved_status)
{
	char	**argv;
	int		exit_status;
	t_error	err;

	err = sig_build_argv(&argv, cmd->data);
	if (err.type)
		return (err);
	err = builtin_eval(2, argv, NULL, &exit_status);
	err = error_drop_non_fatal(err);
	if (err.type == ERR_NO)
		err = env_set_last_status(saved_status);
	else if (err.type == ERR_EXIT)
		err = error_priorize(err, env_set_last_status(exit_status));
	else if (err.type == ERR_EXIT_WITH_CURRENT_STATUS)
	{
		err.type = ERR_EXIT;
		err = error_priorize(err, env_set_last_status(saved_status));
	}
	free(argv[0]);
	free(argv[1]);
	free(argv);
	return (err);
}

// TODO: @ret (waiting for eval implementation)
static inline t_error	sig_process_loop(int saved_status)
{
	t_sig_id		sig_id;
	bool			pending;
	t_sig_action	*action;
	t_error			err;

	sig_id = 0;
	err.type = ERR_NO;
	while (err.type == ERR_NO && sig_id < SIG_ID_COUNT)
	{
		pending = g_signals.pending[sig_id];
		action = &g_signals.state.actions[sig_id];
		if (pending == true)
		{
			g_signals.pending[sig_id] = false;
			if (action->type == SIG_TRAPPED)
				err = sig_process_cmd(&action->cmd, saved_status);
		}
		sig_id++;
	}
	return (err);
}

// TODO: @ret (waiting for eval implementation)
t_error	sig_process(void)
{
	int		saved_status;
	t_error	err;

	if (g_signals.has_pending == false)
		return (error(ERR_NO));
	g_signals.has_pending = false;
	err = env_get_last_status(&saved_status);
	if (err.type)
		return (err);
	return (sig_process_loop(saved_status));
}

// TODO: @ret (waiting for eval implementation)
t_error	sig_process_exit(void)
{
	int		saved_status;
	t_error	err;

	if (g_signals.state.exit_action.type != SIG_TRAPPED)
		return (error(ERR_NO));
	err = env_get_last_status(&saved_status);
	if (err.type)
		return (err);
	return (sig_process_cmd(&g_signals.state.exit_action.cmd, saved_status));
}
