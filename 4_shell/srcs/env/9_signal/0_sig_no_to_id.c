/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_sig_no_to_id.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:13:37 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 22:10:29 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig_priv.h"

static inline int	sig_no_to_id_3(int signo)
{
	if (signo == SIGUSR1)
		return (SIGUSR1_ID);
	else if (signo == SIGUSR2)
		return (SIGUSR2_ID);
	return (-1);
}

static inline int	sig_no_to_id_2(int signo)
{
	if (signo == SIGTERM)
		return (SIGTERM_ID);
	else if (signo == SIGURG)
		return (SIGURG_ID);
	else if (signo == SIGTSTP)
		return (SIGTSTP_ID);
	else if (signo == SIGCONT)
		return (SIGCONT_ID);
	else if (signo == SIGCHLD)
		return (SIGCHLD_ID);
	else if (signo == SIGTTIN)
		return (SIGTTIN_ID);
	else if (signo == SIGTTOU)
		return (SIGTTOU_ID);
	else if (signo == SIGXCPU)
		return (SIGXCPU_ID);
	else if (signo == SIGXFSZ)
		return (SIGXFSZ_ID);
	else if (signo == SIGVTALRM)
		return (SIGVTALRM_ID);
	else if (signo == SIGWINCH)
		return (SIGWINCH_ID);
	else
		return (sig_no_to_id_3(signo));
}

int	sig_no_to_id(int signo)
{
	if (signo == SIGHUP)
		return (SIGHUP_ID);
	else if (signo == SIGINT)
		return (SIGINT_ID);
	else if (signo == SIGQUIT)
		return (SIGQUIT_ID);
	else if (signo == SIGILL)
		return (SIGILL_ID);
	else if (signo == SIGTRAP)
		return (SIGTRAP_ID);
	else if (signo == SIGABRT)
		return (SIGABRT_ID);
	else if (signo == SIGFPE)
		return (SIGFPE_ID);
	else if (signo == SIGBUS)
		return (SIGBUS_ID);
	else if (signo == SIGSEGV)
		return (SIGSEGV_ID);
	else if (signo == SIGSYS)
		return (SIGSYS_ID);
	else if (signo == SIGPIPE)
		return (SIGPIPE_ID);
	else if (signo == SIGALRM)
		return (SIGALRM_ID);
	return (sig_no_to_id_2(signo));
}
