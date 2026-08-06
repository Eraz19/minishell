/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_sig_load.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:13:58 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:13:59 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig.h"
#include "sig_priv.h"
#include "options.h"

static inline t_error	sig_err(t_error_type type, const char *message)
{
	return (error_print(error(type), "signal", message, NULL, NULL));
}

static inline t_error	sig_load_ignored_on_entry(t_sig_state *sig_state)
{
	bool				interactive;
	size_t				i;
	int					signo;
	struct sigaction	sa;
	t_error				err;

	err = option_is_active(OPT_INTERACTIVE, &interactive);
	if (err.type || interactive == true)
		return (err);
	i = 0;
	while (i < SIG_ID_COUNT)
	{
		signo = sig_id_to_no((t_sig_id)i);
		if (signo < 0)
			return (sig_err(ERR_INTERNAL, "unrecognized sig_id"));
		if (sigaction(signo, NULL, &sa) != 0)
			return (sig_err(ERR_LIBC, "unable to read sigaction"));
		if (sa.sa_handler == SIG_IGN)
		{
			sig_state->ignored_on_entry[i] = true;
			sig_state->actions[i].type = SIG_IGNORED;
		}
		i++;
	}
	return (error(ERR_NO));
}

static inline t_error	sig_load_exceptions_2(t_error err)
{
#ifdef SIGTTIN
	if (err.type == ERR_NO)
		err = sig_set_default("TTIN");
#endif
#ifdef SIGTTOU
	if (err.type == ERR_NO)
		err = sig_set_default("TTOU");
#endif
#ifdef SIGTSTP
	if (err.type == ERR_NO)
		err = sig_set_default("TSTP");
#endif
	return (err);
}

static inline t_error	sig_load_exceptions(void)
{
	t_error	err;

	err.type = ERR_NO;
#ifdef SIGINT
	if (err.type == ERR_NO)
		err = sig_set_default("INT");
#endif
#ifdef SIGQUIT
	if (err.type == ERR_NO)
		err = sig_set_default("QUIT");
#endif
#ifdef SIGTERM
	if (err.type == ERR_NO)
		err = sig_set_default("TERM");
#endif
	return (sig_load_exceptions_2(err));
}

t_error	sig_load(void)
{
	t_sig_state	*sig_state;
	bool		interactive;
	t_error		err;

	sig_state =&g_signals.state;
	err = sig_load_ignored_on_entry(sig_state);
	if (err.type)
		return (err);
	err = option_is_active(OPT_INTERACTIVE, &interactive);
	if (err.type || interactive == false)
		return (err);
	return (sig_load_exceptions());
}
