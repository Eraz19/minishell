/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_sig_id_to_no.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:13:29 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 22:10:51 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig_priv.h"

static inline int	sig_id_to_no_3(t_sig_id sig_id)
{
	if (sig_id == SIGUSR1_ID)
		return (SIGUSR1);
	else if (sig_id == SIGUSR2_ID)
		return (SIGUSR2);
	return (-1);
}

static inline int	sig_id_to_no_2(t_sig_id sig_id)
{
	if (sig_id == SIGTERM_ID)
		return (SIGTERM);
	else if (sig_id == SIGURG_ID)
		return (SIGURG);
	else if (sig_id == SIGTSTP_ID)
		return (SIGTSTP);
	else if (sig_id == SIGCONT_ID)
		return (SIGCONT);
	else if (sig_id == SIGCHLD_ID)
		return (SIGCHLD);
	else if (sig_id == SIGTTIN_ID)
		return (SIGTTIN);
	else if (sig_id == SIGTTOU_ID)
		return (SIGTTOU);
	else if (sig_id == SIGXCPU_ID)
		return (SIGXCPU);
	else if (sig_id == SIGXFSZ_ID)
		return (SIGXFSZ);
	else if (sig_id == SIGVTALRM_ID)
		return (SIGVTALRM);
	else if (sig_id == SIGWINCH_ID)
		return (SIGWINCH);
	else
		return (sig_id_to_no_3(sig_id));
}

int	sig_id_to_no(t_sig_id sig_id)
{
	if (sig_id == SIGHUP_ID)
		return (SIGHUP);
	else if (sig_id == SIGINT_ID)
		return (SIGINT);
	else if (sig_id == SIGQUIT_ID)
		return (SIGQUIT);
	else if (sig_id == SIGILL_ID)
		return (SIGILL);
	else if (sig_id == SIGTRAP_ID)
		return (SIGTRAP);
	else if (sig_id == SIGABRT_ID)
		return (SIGABRT);
	else if (sig_id == SIGFPE_ID)
		return (SIGFPE);
	else if (sig_id == SIGBUS_ID)
		return (SIGBUS);
	else if (sig_id == SIGSEGV_ID)
		return (SIGSEGV);
	else if (sig_id == SIGSYS_ID)
		return (SIGSYS);
	else if (sig_id == SIGPIPE_ID)
		return (SIGPIPE);
	else if (sig_id == SIGALRM_ID)
		return (SIGALRM);
	return (sig_id_to_no_2(sig_id));
}
