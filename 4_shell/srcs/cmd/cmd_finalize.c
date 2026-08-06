/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_finalize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:56:54 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:05:15 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "sig.h"
#include "options.h"
#ifdef DEBUG_CMD
# include "debug.h"	// DEBUG
#endif

static inline t_error	cmd_qualify_error(t_cmd *cmd, t_error err, int *status)
{
	bool	interactive;
	int		signo;
	t_error	option_err;

	(void)error_print(err, cmd->name.data, NULL, NULL);
	if (err.type == ERR_INTERRUPTED)
	{
		if (sig_has_pending_trap(&signo))
			*status = ERR_POSIX_SIGNAL_BASE_CODE + signo;
		err.type = ERR_NO;
	}
	else if (err.type == ERR_REDIRECTION
		&& cmd->entry.type != CMD_SPECIAL_BUILTIN)
		err.type = ERR_NO;
	else if (err.type == ERR_POSIX_CMD_NOT_FOUND
		|| err.type == ERR_POSIX_CMD_NOT_EXECUTABLE)
		err.type = ERR_NO;
	else if (err.type > ERR_POSIX_SYNTAX && err.type < ERR_POSIX_READ)
	{
		option_err = option_is_active(OPT_INTERACTIVE, &interactive);
		if (option_err.type)
			err = error_priorize(err, option_err);
		else if (interactive == true)
			err.type = ERR_NO;
	}
	return (err);
}

t_error	cmd_finalize(t_cmd *cmd, t_error err, int *exit_status)
{
	/* ---------- DEBUG (START) ---------- */
#ifdef DEBUG_CMD
	int			initial_exit_status;
	t_error		initial_error;
	const char	*prefix;

	initial_exit_status = *exit_status;
	initial_error = err;
#endif
	/* ---------- DEBUG (END) ---------- */
	if (*exit_status < 0)
		*exit_status = (int)err.type;
	if (err.type && error_is_flow_control(err) == false)
		err = cmd_qualify_error(cmd, err, exit_status);
	/* ---------- DEBUG (START) ---------- */
#ifdef DEBUG_CMD
	if (cmd->entry.type == CMD_BUILTIN)
		prefix = "BUILTIN ";
	else if (cmd->entry.type == CMD_SPECIAL_BUILTIN)
		prefix = "SPECIAL BUILTIN ";
	else if (cmd->entry.type == CMD_EXTERNAL)
		prefix = "EXTERNAL ";
	else
		prefix = "";
	if (cmd->entry.type == CMD_NONE)
		fprintf(stderr, MAGENTA "############## %s%s (START) ##############\n" NC, prefix, cmd->name.data);
	fprintf(stderr, MAGENTA "############## %s%s (STOP) ###############\n" NC, prefix, cmd->name.data);
	fprintf(stderr, "[CMD   ] type        => %s\n", cmd_type_to_string(cmd->entry.type));
	fprintf(stderr, "[CMD   ] exit_status => %i => %i\n", initial_exit_status, *exit_status);
	fprintf(stderr, "[CMD   ] error       => %s => %s\n", error_to_string(initial_error), error_to_string(err));
#endif
	/* ---------- DEBUG (END) ---------- */
	sig_process();
	return (err);
}

t_error	cmd_finalize_and_free(t_cmd *cmd, t_error err, int *exit_status)
{
	err = cmd_finalize(cmd, err, exit_status);
	cmd_free(cmd);
	return (err);
}
