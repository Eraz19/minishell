/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_build_name_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:13:18 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:13:19 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig_build_name_priv.h"

static inline t_error	sig_build_name_2_e(t_sig_id sig_id, t_string *out_name)
{
#ifdef SIGFREEZE
	if (sig_id == SIGFREEZE_ID)
		return (sig_build_name_set("FREEZE", out_name));
#endif
#ifdef SIGTHAW
	if (sig_id == SIGTHAW_ID)
		return (sig_build_name_set("THAW", out_name));
#endif
#ifdef SIGCANCEL
	if (sig_id == SIGCANCEL_ID)
		return (sig_build_name_set("CANCEL", out_name));
#endif
	(void)sig_id;
	(void)out_name;
	return (error(ERR_INTERNAL));
}

static inline t_error	sig_build_name_2_d(t_sig_id sig_id, t_string *out_name)
{
#ifdef SIGSTKFLT
	if (sig_id == SIGSTKFLT_ID)
		return (sig_build_name_set("STKFLT", out_name));
#endif
#ifdef SIGUNUSED
	if (sig_id == SIGUNUSED_ID)
		return (sig_build_name_set("UNUSED", out_name));
#endif
#ifdef SIGTHR
	if (sig_id == SIGTHR_ID)
		return (sig_build_name_set("THR", out_name));
#endif
#ifdef SIGLIBRT
	if (sig_id == SIGLIBRT_ID)
		return (sig_build_name_set("LIBRT", out_name));
#endif
#ifdef SIGWAITING
	if (sig_id == SIGWAITING_ID)
		return (sig_build_name_set("WAITING", out_name));
#endif
#ifdef SIGLWP
	if (sig_id == SIGLWP_ID)
		return (sig_build_name_set("LWP", out_name));
#endif
	return (sig_build_name_2_e(sig_id, out_name));
}

static inline t_error	sig_build_name_2_c(t_sig_id sig_id, t_string *out_name)
{
#ifdef SIGUSR1
	if (sig_id == SIGUSR1_ID)
		return (sig_build_name_set("USR1", out_name));
#endif
#ifdef SIGUSR2
	if (sig_id == SIGUSR2_ID)
		return (sig_build_name_set("USR2", out_name));
#endif
#ifdef SIGPOLL
	if (sig_id == SIGPOLL_ID)
		return (sig_build_name_set("POLL", out_name));
#endif
#ifdef SIGCLD
	if (sig_id == SIGCLD_ID)
		return (sig_build_name_set("CLD", out_name));
#endif
#ifdef SIGPWR
	if (sig_id == SIGPWR_ID)
		return (sig_build_name_set("PWR", out_name));
#endif
#ifdef SIGLOST
	if (sig_id == SIGLOST_ID)
		return (sig_build_name_set("LOST", out_name));
#endif
	return (sig_build_name_2_d(sig_id, out_name));
}

static inline t_error	sig_build_name_2_b(t_sig_id sig_id, t_string *out_name)
{
#ifdef SIGXCPU
	if (sig_id == SIGXCPU_ID)
		return (sig_build_name_set("XCPU", out_name));
#endif
#ifdef SIGXFSZ
	if (sig_id == SIGXFSZ_ID)
		return (sig_build_name_set("XFSZ", out_name));
#endif
#ifdef SIGVTALRM
	if (sig_id == SIGVTALRM_ID)
		return (sig_build_name_set("VTALRM", out_name));
#endif
#ifdef SIGPROF
	if (sig_id == SIGPROF_ID)
		return (sig_build_name_set("PROF", out_name));
#endif
#ifdef SIGWINCH
	if (sig_id == SIGWINCH_ID)
		return (sig_build_name_set("WINCH", out_name));
#endif
#ifdef SIGINFO
	if (sig_id == SIGINFO_ID)
		return (sig_build_name_set("INFO", out_name));
#endif
	return (sig_build_name_2_c(sig_id, out_name));
}

t_error	sig_build_name_2(t_sig_id sig_id, t_string *out_name)
{
#ifdef SIGTSTP
	if (sig_id == SIGTSTP_ID)
		return (sig_build_name_set("TSTP", out_name));
#endif
#ifdef SIGCONT
	if (sig_id == SIGCONT_ID)
		return (sig_build_name_set("CONT", out_name));
#endif
#ifdef SIGCHLD
	if (sig_id == SIGCHLD_ID)
		return (sig_build_name_set("CHLD", out_name));
#endif
#ifdef SIGTTIN
	if (sig_id == SIGTTIN_ID)
		return (sig_build_name_set("TTIN", out_name));
#endif
#ifdef SIGTTOU
	if (sig_id == SIGTTOU_ID)
		return (sig_build_name_set("TTOU", out_name));
#endif
#ifdef SIGIO
	if (sig_id == SIGIO_ID)
		return (sig_build_name_set("IO", out_name));
#endif
	return (sig_build_name_2_b(sig_id, out_name));
}
