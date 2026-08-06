/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_no_to_id_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:13:33 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:13:34 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig_no_to_id_priv.h"

static inline int	sig_no_to_id_2_e(int signo)
{
#ifdef SIGFREEZE
	if (signo == SIGFREEZE)
		return (SIGFREEZE_ID);
#endif
#ifdef SIGTHAW
	if (signo == SIGTHAW)
		return (SIGTHAW_ID);
#endif
#ifdef SIGCANCEL
	if (signo == SIGCANCEL)
		return (SIGCANCEL_ID);
#endif
	(void)signo;
	return (-1);
}

static inline int	sig_no_to_id_2_d(int signo)
{
#ifdef SIGSTKFLT
	if (signo == SIGSTKFLT)
		return (SIGSTKFLT_ID);
#endif
#ifdef SIGUNUSED
	if (signo == SIGUNUSED)
		return (SIGUNUSED_ID);
#endif
#ifdef SIGTHR
	if (signo == SIGTHR)
		return (SIGTHR_ID);
#endif
#ifdef SIGLIBRT
	if (signo == SIGLIBRT)
		return (SIGLIBRT_ID);
#endif
#ifdef SIGWAITING
	if (signo == SIGWAITING)
		return (SIGWAITING_ID);
#endif
#ifdef SIGLWP
	if (signo == SIGLWP)
		return (SIGLWP_ID);
#endif
	return (sig_no_to_id_2_e(signo));
}

static inline int	sig_no_to_id_2_c(int signo)
{
#ifdef SIGUSR1
	if (signo == SIGUSR1)
		return (SIGUSR1_ID);
#endif
#ifdef SIGUSR2
	if (signo == SIGUSR2)
		return (SIGUSR2_ID);
#endif
#ifdef SIGPOLL
	if (signo == SIGPOLL)
		return (SIGPOLL_ID);
#endif
#ifdef SIGCLD
	if (signo == SIGCLD)
		return (SIGCLD_ID);
#endif
#ifdef SIGPWR
	if (signo == SIGPWR)
		return (SIGPWR_ID);
#endif
#ifdef SIGLOST
	if (signo == SIGLOST)
		return (SIGLOST_ID);
#endif
	return (sig_no_to_id_2_d(signo));
}

static inline int	sig_no_to_id_2_b(int signo)
{
#ifdef SIGXCPU
	if (signo == SIGXCPU)
		return (SIGXCPU_ID);
#endif
#ifdef SIGXFSZ
	if (signo == SIGXFSZ)
		return (SIGXFSZ_ID);
#endif
#ifdef SIGVTALRM
	if (signo == SIGVTALRM)
		return (SIGVTALRM_ID);
#endif
#ifdef SIGPROF
	if (signo == SIGPROF)
		return (SIGPROF_ID);
#endif
#ifdef SIGWINCH
	if (signo == SIGWINCH)
		return (SIGWINCH_ID);
#endif
#ifdef SIGINFO
	if (signo == SIGINFO)
		return (SIGINFO_ID);
#endif
	return (sig_no_to_id_2_c(signo));
}

int	sig_no_to_id_2(int signo)
{
#ifdef SIGTSTP
	if (signo == SIGTSTP)
		return (SIGTSTP_ID);
#endif
#ifdef SIGCONT
	if (signo == SIGCONT)
		return (SIGCONT_ID);
#endif
#ifdef SIGCHLD
	if (signo == SIGCHLD)
		return (SIGCHLD_ID);
#endif
#ifdef SIGTTIN
	if (signo == SIGTTIN)
		return (SIGTTIN_ID);
#endif
#ifdef SIGTTOU
	if (signo == SIGTTOU)
		return (SIGTTOU_ID);
#endif
#ifdef SIGIO
	if (signo == SIGIO)
		return (SIGIO_ID);
#endif
	return (sig_no_to_id_2_b(signo));
}
