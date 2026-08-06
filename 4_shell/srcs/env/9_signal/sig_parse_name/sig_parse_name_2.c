/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_parse_name_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:13:42 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:13:43 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig_parse_name_priv.h"
#include "libft.h"

static inline t_error	sig_parse_name_2_e(
	const char *name,
	int *out_signo,
	t_sig_id *out_sig_id)
{
#ifdef SIGFREEZE
	if (str_cmp(name, "FREEZE") == 0)
		return (sig_parse_name_set(SIGFREEZE, SIGFREEZE_ID, out_signo, out_sig_id));
#endif
#ifdef SIGTHAW
	if (str_cmp(name, "THAW") == 0)
		return (sig_parse_name_set(SIGTHAW, SIGTHAW_ID, out_signo, out_sig_id));
#endif
#ifdef SIGCANCEL
	if (str_cmp(name, "CANCEL") == 0)
		return (sig_parse_name_set(SIGCANCEL, SIGCANCEL_ID, out_signo, out_sig_id));
#endif
	(void)name;
	(void)out_signo;
	(void)out_sig_id;
	return (error(ERR_VAR_INVALID_NAME));
}

static inline t_error	sig_parse_name_2_d(
	const char *name,
	int *out_signo,
	t_sig_id *out_sig_id)
{
#ifdef SIGSTKFLT
	if (str_cmp(name, "STKFLT") == 0)
		return (sig_parse_name_set(SIGSTKFLT, SIGSTKFLT_ID, out_signo, out_sig_id));
#endif
#ifdef SIGUNUSED
	if (str_cmp(name, "UNUSED") == 0)
		return (sig_parse_name_set(SIGUNUSED, SIGUNUSED_ID, out_signo, out_sig_id));
#endif
#ifdef SIGTHR
	if (str_cmp(name, "THR") == 0)
		return (sig_parse_name_set(SIGTHR, SIGTHR_ID, out_signo, out_sig_id));
#endif
#ifdef SIGLIBRT
	if (str_cmp(name, "LIBRT") == 0)
		return (sig_parse_name_set(SIGLIBRT, SIGLIBRT_ID, out_signo, out_sig_id));
#endif
#ifdef SIGWAITING
	if (str_cmp(name, "WAITING") == 0)
		return (sig_parse_name_set(SIGWAITING, SIGWAITING_ID, out_signo, out_sig_id));
#endif
#ifdef SIGLWP
	if (str_cmp(name, "LWP") == 0)
		return (sig_parse_name_set(SIGLWP, SIGLWP_ID, out_signo, out_sig_id));
#endif
	return (sig_parse_name_2_e(name, out_signo, out_sig_id));
}

static inline t_error	sig_parse_name_2_c(
	const char *name,
	int *out_signo,
	t_sig_id *out_sig_id)
{
#ifdef SIGUSR1
	if (str_cmp(name, "USR1") == 0)
		return (sig_parse_name_set(SIGUSR1, SIGUSR1_ID, out_signo, out_sig_id));
#endif
#ifdef SIGUSR2
	if (str_cmp(name, "USR2") == 0)
		return (sig_parse_name_set(SIGUSR2, SIGUSR2_ID, out_signo, out_sig_id));
#endif
#ifdef SIGPOLL
	if (str_cmp(name, "POLL") == 0)
		return (sig_parse_name_set(SIGPOLL, SIGPOLL_ID, out_signo, out_sig_id));
#endif
#ifdef SIGCLD
	if (str_cmp(name, "CLD") == 0)
		return (sig_parse_name_set(SIGCLD, SIGCLD_ID, out_signo, out_sig_id));
#endif
#ifdef SIGPWR
	if (str_cmp(name, "PWR") == 0)
		return (sig_parse_name_set(SIGPWR, SIGPWR_ID, out_signo, out_sig_id));
#endif
#ifdef SIGLOST
	if (str_cmp(name, "LOST") == 0)
		return (sig_parse_name_set(SIGLOST, SIGLOST_ID, out_signo, out_sig_id));
#endif
	return (sig_parse_name_2_d(name, out_signo, out_sig_id));
}

static inline t_error	sig_parse_name_2_b(
	const char *name,
	int *out_signo,
	t_sig_id *out_sig_id)
{
#ifdef SIGXCPU
	if (str_cmp(name, "XCPU") == 0)
		return (sig_parse_name_set(SIGXCPU, SIGXCPU_ID, out_signo, out_sig_id));
#endif
#ifdef SIGXFSZ
	if (str_cmp(name, "XFSZ") == 0)
		return (sig_parse_name_set(SIGXFSZ, SIGXFSZ_ID, out_signo, out_sig_id));
#endif
#ifdef SIGVTALRM
	if (str_cmp(name, "VTALRM") == 0)
		return (sig_parse_name_set(SIGVTALRM, SIGVTALRM_ID, out_signo, out_sig_id));
#endif
#ifdef SIGPROF
	if (str_cmp(name, "PROF") == 0)
		return (sig_parse_name_set(SIGPROF, SIGPROF_ID, out_signo, out_sig_id));
#endif
#ifdef SIGWINCH
	if (str_cmp(name, "WINCH") == 0)
		return (sig_parse_name_set(SIGWINCH, SIGWINCH_ID, out_signo, out_sig_id));
#endif
#ifdef SIGINFO
	if (str_cmp(name, "INFO") == 0)
		return (sig_parse_name_set(SIGINFO, SIGINFO_ID, out_signo, out_sig_id));
#endif
	return (sig_parse_name_2_c(name, out_signo, out_sig_id));
}

t_error	sig_parse_name_2(
	const char *name,
	int *out_signo,
	t_sig_id *out_sig_id)
{
#ifdef SIGTSTP
	if (str_cmp(name, "TSTP") == 0)
		return (sig_parse_name_set(SIGTSTP, SIGTSTP_ID, out_signo, out_sig_id));
#endif
#ifdef SIGCONT
	if (str_cmp(name, "CONT") == 0)
		return (sig_parse_name_set(SIGCONT, SIGCONT_ID, out_signo, out_sig_id));
#endif
#ifdef SIGCHLD
	if (str_cmp(name, "CHLD") == 0)
		return (sig_parse_name_set(SIGCHLD, SIGCHLD_ID, out_signo, out_sig_id));
#endif
#ifdef SIGTTIN
	if (str_cmp(name, "TTIN") == 0)
		return (sig_parse_name_set(SIGTTIN, SIGTTIN_ID, out_signo, out_sig_id));
#endif
#ifdef SIGTTOU
	if (str_cmp(name, "TTOU") == 0)
		return (sig_parse_name_set(SIGTTOU, SIGTTOU_ID, out_signo, out_sig_id));
#endif
#ifdef SIGIO
	if (str_cmp(name, "IO") == 0)
		return (sig_parse_name_set(SIGIO, SIGIO_ID, out_signo, out_sig_id));
#endif
	return (sig_parse_name_2_b(name, out_signo, out_sig_id));
}
