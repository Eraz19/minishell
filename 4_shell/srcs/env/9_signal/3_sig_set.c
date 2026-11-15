/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_sig_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:13:56 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:13:57 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig.h"
#include "sig_priv.h"
#include "options.h"

static inline t_error	sig_error_if_ignored_on_entry(t_sig_id sig_id)
{
	t_sig_state	*sig_state;

	sig_state = &g_signals.state;
	if (sig_state->ignored_on_entry[sig_id] == true)
		return (error(ERR_SIG_WAS_IGNORED_ON_ENTRY));
	return (error(ERR_NO));
}

t_error	sig_set_trap(const char *sig_name, const char *cmd)
{
	t_string		cmd_string;
	int				signo;
	t_sig_id		sig_id;
	t_sig_action	*action;
	t_error			err;

	g_signals.trap_with_operand_has_been_executed = true;
	if (!string_init(&cmd_string, 0, cmd, -1))
		return (error_sys());
	if (str_cmp("EXIT", sig_name) == 0 || str_cmp("0", sig_name) == 0)
	{
		string_free(&g_signals.state.exit_action.cmd);
		g_signals.state.exit_action.cmd = cmd_string;
		g_signals.state.exit_action.type = SIG_TRAPPED;
		return (error(ERR_NO));
	}
	err = sig_parse_name(sig_name, &signo, &sig_id);
	if (err.type)
		return (string_free(&cmd_string), err);
	err = sig_error_if_ignored_on_entry(sig_id);
	if (err.type)
		return (string_free(&cmd_string), err);
	action = &g_signals.state.actions[sig_id];
	return (sig_install_trap(action, signo, &cmd_string));
}

static inline t_error	sig_set_shell_default(t_sig_action *action, int signo)
{
	bool	interactive;
	t_error	err;

	err = option_is_active(OPT_INTERACTIVE, &interactive);
	if (err.type)
		return (err);
	if (interactive == false)
		return (sig_install_default(action, signo));
	else if (signo == SIGINT)
		return (sig_install_shell_default_sigint(action));
	else if (signo == SIGQUIT || signo == SIGTERM
		|| signo == SIGTTIN || signo == SIGTTOU || signo == SIGTSTP)
	{
		err = sig_install_ignore(action, signo);
		if (err.type == ERR_NO)
			action->type = SIG_DEFAULT;
		return (err);
	}
	return (sig_install_default(action, signo));
}

t_error	sig_set_default(const char *sig_name)
{
	t_sig_state		*sig_state;
	int				signo;
	t_sig_id		sig_id;
	t_sig_action	*action;
	t_error			err;

	g_signals.trap_with_operand_has_been_executed = true;
	sig_state = &g_signals.state;
	if (str_cmp("EXIT", sig_name) == 0 || str_cmp("0", sig_name) == 0)
	{
		string_free(&sig_state->exit_action.cmd);
		sig_state->exit_action.type = SIG_DEFAULT;
		return (error(ERR_NO));
	}
	err = sig_parse_name(sig_name, &signo, &sig_id);
	if (err.type)
		return (err);
	err = sig_error_if_ignored_on_entry(sig_id);
	if (err.type)
		return (err);
	action = &sig_state->actions[sig_id];
	return (sig_set_shell_default(action, signo));
}

t_error	sig_set_ignore(const char *sig_name)
{
	t_sig_state		*sig_state;
	int				signo;
	t_sig_id		sig_id;
	t_sig_action	*action;
	t_error			err;

	g_signals.trap_with_operand_has_been_executed = true;
	sig_state = &g_signals.state;
	if (str_cmp("EXIT", sig_name) == 0 || str_cmp("0", sig_name) == 0)
	{
		string_free(&sig_state->exit_action.cmd);
		sig_state->exit_action.type = SIG_IGNORED;
		return (error(ERR_NO));
	}
	err = sig_parse_name(sig_name, &signo, &sig_id);
	if (err.type)
		return (err);
	action = &sig_state->actions[sig_id];
	return (sig_install_ignore(action, signo));
}
