/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_id_to_no.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:13:29 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:13:30 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig_priv.h"
#include "sig_id_to_no_priv.h"

static inline int	sig_id_to_no_1_c(t_sig_id sig_id)
{
#ifdef SIGSYS
	if (sig_id == SIGSYS_ID)
		return (SIGSYS);
#endif
#ifdef SIGPIPE
	if (sig_id == SIGPIPE_ID)
		return (SIGPIPE);
#endif
#ifdef SIGALRM
	if (sig_id == SIGALRM_ID)
		return (SIGALRM);
#endif
#ifdef SIGTERM
	if (sig_id == SIGTERM_ID)
		return (SIGTERM);
#endif
#ifdef SIGURG
	if (sig_id == SIGURG_ID)
		return (SIGURG);
#endif
	return (sig_id_to_no_2(sig_id));
}

static inline int	sig_id_to_no_1_b(t_sig_id sig_id)
{
#ifdef SIGIOT
	if (sig_id == SIGIOT_ID)
		return (SIGIOT);
#endif
#ifdef SIGEMT
	if (sig_id == SIGEMT_ID)
		return (SIGEMT);
#endif
#ifdef SIGFPE
	if (sig_id == SIGFPE_ID)
		return (SIGFPE);
#endif
#ifdef SIGBUS
	if (sig_id == SIGBUS_ID)
		return (SIGBUS);
#endif
#ifdef SIGSEGV
	if (sig_id == SIGSEGV_ID)
		return (SIGSEGV);
#endif
	return (sig_id_to_no_1_c(sig_id));
}

int	sig_id_to_no(t_sig_id sig_id)
{
#ifdef SIGHUP
	if (sig_id == SIGHUP_ID)
		return (SIGHUP);
#endif
#ifdef SIGINT
	if (sig_id == SIGINT_ID)
		return (SIGINT);
#endif
#ifdef SIGQUIT
	if (sig_id == SIGQUIT_ID)
		return (SIGQUIT);
#endif
#ifdef SIGILL
	if (sig_id == SIGILL_ID)
		return (SIGILL);
#endif
#ifdef SIGTRAP
	if (sig_id == SIGTRAP_ID)
		return (SIGTRAP);
#endif
#ifdef SIGABRT
	if (sig_id == SIGABRT_ID)
		return (SIGABRT);
#endif
	return (sig_id_to_no_1_b(sig_id));
}
