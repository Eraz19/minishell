/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_parse_name.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:13:46 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:13:47 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig_priv.h"
#include "sig_parse_name_priv.h"
#include "libft.h"

static inline t_error	sig_parse_name_1_c(
	const char *name,
	int *out_signo,
	t_sig_id *out_sig_id)
{
#ifdef SIGSYS
	if (str_cmp(name, "SYS") == 0)
		return (sig_parse_name_set(SIGSYS, SIGSYS_ID, out_signo, out_sig_id));
#endif
#ifdef SIGPIPE
	if (str_cmp(name, "PIPE") == 0)
		return (sig_parse_name_set(SIGPIPE, SIGPIPE_ID, out_signo, out_sig_id));
#endif
#ifdef SIGALRM
	if (str_cmp(name, "ALRM") == 0 || str_cmp(name, "14") == 0)
		return (sig_parse_name_set(SIGALRM, SIGALRM_ID, out_signo, out_sig_id));
#endif
#ifdef SIGTERM
	if (str_cmp(name, "TERM") == 0 || str_cmp(name, "15") == 0)
		return (sig_parse_name_set(SIGTERM, SIGTERM_ID, out_signo, out_sig_id));
#endif
#ifdef SIGURG
	if (str_cmp(name, "URG") == 0)
		return (sig_parse_name_set(SIGURG, SIGURG_ID, out_signo, out_sig_id));
#endif
	return (sig_parse_name_2(name, out_signo, out_sig_id));
}

static inline t_error	sig_parse_name_1_b(
	const char *name,
	int *out_signo,
	t_sig_id *out_sig_id)
{
#ifdef SIGIOT
	if (str_cmp(name, "IOT") == 0)
		return (sig_parse_name_set(SIGIOT, SIGIOT_ID, out_signo, out_sig_id));
#endif
#ifdef SIGEMT
	if (str_cmp(name, "EMT") == 0)
		return (sig_parse_name_set(SIGEMT, SIGEMT_ID, out_signo, out_sig_id));
#endif
#ifdef SIGFPE
	if (str_cmp(name, "FPE") == 0)
		return (sig_parse_name_set(SIGFPE, SIGFPE_ID, out_signo, out_sig_id));
#endif
#ifdef SIGBUS
	if (str_cmp(name, "BUS") == 0)
		return (sig_parse_name_set(SIGBUS, SIGBUS_ID, out_signo, out_sig_id));
#endif
#ifdef SIGSEGV
	if (str_cmp(name, "SEGV") == 0)
		return (sig_parse_name_set(SIGSEGV, SIGSEGV_ID, out_signo, out_sig_id));
#endif
	return (sig_parse_name_1_c(name, out_signo, out_sig_id));
}

t_error	sig_parse_name(
	const char *name,
	int *out_signo,
	t_sig_id *out_sig_id)
{
#ifdef SIGHUP
	if (str_cmp(name, "HUP") == 0 || str_cmp(name, "1") == 0)
		return (sig_parse_name_set(SIGHUP, SIGHUP_ID, out_signo, out_sig_id));
#endif
#ifdef SIGINT
	if (str_cmp(name, "INT") == 0 || str_cmp(name, "2") == 0)
		return (sig_parse_name_set(SIGINT, SIGINT_ID, out_signo, out_sig_id));
#endif
#ifdef SIGQUIT
	if (str_cmp(name, "QUIT") == 0 || str_cmp(name, "3") == 0)
		return (sig_parse_name_set(SIGQUIT, SIGQUIT_ID, out_signo, out_sig_id));
#endif
#ifdef SIGILL
	if (str_cmp(name, "ILL") == 0)
		return (sig_parse_name_set(SIGILL, SIGILL_ID, out_signo, out_sig_id));
#endif
#ifdef SIGTRAP
	if (str_cmp(name, "TRAP") == 0)
		return (sig_parse_name_set(SIGTRAP, SIGTRAP_ID, out_signo, out_sig_id));
#endif
#ifdef SIGABRT
	if (str_cmp(name, "ABRT") == 0 || str_cmp(name, "6") == 0)
		return (sig_parse_name_set(SIGABRT, SIGABRT_ID, out_signo, out_sig_id));
#endif
	return (sig_parse_name_1_b(name, out_signo, out_sig_id));
}
