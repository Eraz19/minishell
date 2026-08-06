/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_build_name.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:13:18 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 22:01:58 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig_priv.h"

static inline t_error	sig_build_name_set(const char *name, t_string *out_name)
{
	if (!string_init(out_name, 0, name, -1))
		return (error_sys());
	return (error(ERR_NO));
}

static inline t_error	sig_build_name_3(t_sig_id sig_id, t_string *out_name)
{
	if (sig_id == SIGUSR1_ID)
		return (sig_build_name_set("USR1", out_name));
	else if (sig_id == SIGUSR2_ID)
		return (sig_build_name_set("USR2", out_name));
	return (error(ERR_VAR_NOT_FOUND));
}

static inline t_error	sig_build_name_2(t_sig_id sig_id, t_string *out_name)
{
	if (sig_id == SIGTERM_ID)
		return (sig_build_name_set("TERM", out_name));
	else if (sig_id == SIGURG_ID)
		return (sig_build_name_set("URG", out_name));
	else if (sig_id == SIGTSTP_ID)
		return (sig_build_name_set("TSTP", out_name));
	else if (sig_id == SIGCONT_ID)
		return (sig_build_name_set("CONT", out_name));
	else if (sig_id == SIGCHLD_ID)
		return (sig_build_name_set("CHLD", out_name));
	else if (sig_id == SIGTTIN_ID)
		return (sig_build_name_set("TTIN", out_name));
	else if (sig_id == SIGTTOU_ID)
		return (sig_build_name_set("TTOU", out_name));
	else if (sig_id == SIGXCPU_ID)
		return (sig_build_name_set("XCPU", out_name));
	else if (sig_id == SIGXFSZ_ID)
		return (sig_build_name_set("XFSZ", out_name));
	else if (sig_id == SIGVTALRM_ID)
		return (sig_build_name_set("VTALRM", out_name));
	else if (sig_id == SIGWINCH_ID)
		return (sig_build_name_set("WINCH", out_name));
	else
		return (sig_build_name_3(sig_id, out_name));
}

t_error	sig_build_name(t_sig_id sig_id, t_string *out_name)
{
	if (sig_id == SIGHUP_ID)
		return (sig_build_name_set("HUP", out_name));
	else if (sig_id == SIGINT_ID)
		return (sig_build_name_set("INT", out_name));
	else if (sig_id == SIGQUIT_ID)
		return (sig_build_name_set("QUIT", out_name));
	else if (sig_id == SIGILL_ID)
		return (sig_build_name_set("ILL", out_name));
	else if (sig_id == SIGTRAP_ID)
		return (sig_build_name_set("TRAP", out_name));
	else if (sig_id == SIGABRT_ID)
		return (sig_build_name_set("ABRT", out_name));
	else if (sig_id == SIGFPE_ID)
		return (sig_build_name_set("FPE", out_name));
	else if (sig_id == SIGBUS_ID)
		return (sig_build_name_set("BUS", out_name));
	else if (sig_id == SIGSEGV_ID)
		return (sig_build_name_set("SEGV", out_name));
	else if (sig_id == SIGSYS_ID)
		return (sig_build_name_set("SYS", out_name));
	else if (sig_id == SIGPIPE_ID)
		return (sig_build_name_set("PIPE", out_name));
	else if (sig_id == SIGALRM_ID)
		return (sig_build_name_set("ALRM", out_name));
	return (sig_build_name_2(sig_id, out_name));
}
