/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_sig_install.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:13:54 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:13:55 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig_priv.h"
#include "options.h"

#define ERR_INSTALL	"unable to install handler"
#define ERR_DFL		"unable to set default handler"
#define ERR_IGNORE	"unable to ignore signal"

static void	sig_handler(int signo)
{
	int	index;

	index = sig_no_to_id(signo);
	if (index < 0)
		return ;
	g_signals.pending[index] = 1;
	g_signals.has_pending = 1;
}

t_error	sig_install_shell_default_sigint(t_sig_action *sig_action)
{
	struct sigaction	sa;
	bool				interactive;
	t_error				err;

	if (g_signals.state.ignored_on_entry[SIGINT_ID] == true)
		return (error(ERR_NO));
	err = option_is_active(OPT_INTERACTIVE, &interactive);
	if (err.type)
		return (err);
	else if (interactive == true)
		sa.sa_handler = sig_handler;
	else
		sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) != 0)
	{
		err = error_sys();
		return (error_print(err, ERR_INSTALL, NULL, "signal %i", SIGINT));
	}
	sig_action->type = SIG_DEFAULT;
	string_free(&sig_action->cmd);
	return (error(ERR_NO));
}

t_error	sig_install_trap(t_sig_action *sig_action, int signo, t_string *cmd)
{
	struct sigaction	sa;
	t_error				err;

	sa.sa_handler = sig_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(signo, &sa, NULL) != 0)
	{
		err = error_sys();
		string_free(cmd);
		return (error_print(err, ERR_INSTALL, NULL, "signal %i", signo));
	}
	string_free(&sig_action->cmd);
	string_take_string(&sig_action->cmd, cmd);
	sig_action->type = SIG_TRAPPED;
	return (error(ERR_NO));
}

t_error	sig_install_default(t_sig_action *sig_action, int signo)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(signo, &sa, NULL) != 0)
		return (error_print(error_sys(), ERR_DFL, NULL, "signal %i", signo));
	string_free(&sig_action->cmd);
	sig_action->type = SIG_DEFAULT;
	return (error(ERR_NO));
}

t_error	sig_install_ignore(t_sig_action *sig_action, int signo)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(signo, &sa, NULL) != 0)
		return (error_print(error_sys(), ERR_IGNORE, NULL, "signal %i", signo));
	string_free(&sig_action->cmd);
	sig_action->type = SIG_IGNORED;
	return (error(ERR_NO));
}
