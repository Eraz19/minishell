/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_finalize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:56:54 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 21:26:45 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
#include "sig.h"
#include "options.h"

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
	else if (err.type == ERR_POSIX_CMD_NFOUND || err.type == ERR_POSIX_CMD_NEXC)
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
	if (*exit_status < 0)
		*exit_status = (int)err.type;
	if (err.type && error_is_flow_control(err) == false)
		err = cmd_qualify_error(cmd, err, exit_status);
	sig_process();
	return (err);
}

t_error	cmd_finalize_and_free(t_cmd *cmd, t_error err, int *exit_status)
{
	err = cmd_finalize(cmd, err, exit_status);
	cmd_free(cmd);
	return (err);
}
