/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_no_to_id.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:13:37 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:13:38 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig_priv.h"
#include "sig_no_to_id_priv.h"

static inline int	sig_no_to_id_1_c(int signo)
{
#ifdef SIGSYS
	if (signo == SIGSYS)
		return (SIGSYS_ID);
#endif
#ifdef SIGPIPE
	if (signo == SIGPIPE)
		return (SIGPIPE_ID);
#endif
#ifdef SIGALRM
	if (signo == SIGALRM)
		return (SIGALRM_ID);
#endif
#ifdef SIGTERM
	if (signo == SIGTERM)
		return (SIGTERM_ID);
#endif
#ifdef SIGURG
	if (signo == SIGURG)
		return (SIGURG_ID);
#endif
	return (sig_no_to_id_2(signo));
}

static inline int	sig_no_to_id_1_b(int signo)
{
#ifdef SIGIOT
	if (signo == SIGIOT)
		return (SIGIOT_ID);
#endif
#ifdef SIGEMT
	if (signo == SIGEMT)
		return (SIGEMT_ID);
#endif
#ifdef SIGFPE
	if (signo == SIGFPE)
		return (SIGFPE_ID);
#endif
#ifdef SIGBUS
	if (signo == SIGBUS)
		return (SIGBUS_ID);
#endif
#ifdef SIGSEGV
	if (signo == SIGSEGV)
		return (SIGSEGV_ID);
#endif
	return (sig_no_to_id_1_c(signo));
}

int	sig_no_to_id(int signo)
{
#ifdef SIGHUP
	if (signo == SIGHUP)
		return (SIGHUP_ID);
#endif
#ifdef SIGINT
	if (signo == SIGINT)
		return (SIGINT_ID);
#endif
#ifdef SIGQUIT
	if (signo == SIGQUIT)
		return (SIGQUIT_ID);
#endif
#ifdef SIGILL
	if (signo == SIGILL)
		return (SIGILL_ID);
#endif
#ifdef SIGTRAP
	if (signo == SIGTRAP)
		return (SIGTRAP_ID);
#endif
#ifdef SIGABRT
	if (signo == SIGABRT)
		return (SIGABRT_ID);
#endif
	return (sig_no_to_id_1_b(signo));
}
