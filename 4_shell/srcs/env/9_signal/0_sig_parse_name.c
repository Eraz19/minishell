/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_sig_parse_name.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:13:46 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 22:15:43 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig_priv.h"
#include "libft.h"

static inline t_error	sig_parse_name_set(
							int signo,
							t_sig_id sig_id,
							int *out_signo,
							t_sig_id *out_sig_id)
{
	*out_signo = signo;
	*out_sig_id = sig_id;
	return (error(ERR_NO));
}

static inline t_error	sig_parse_name_3(
							const char *name,
							int *out_signo,
							t_sig_id *out_sig_id)
{
	if (str_cmp(name, "USR1") == 0)
		return (sig_parse_name_set(SIGUSR1, SIGUSR1_ID, out_signo, out_sig_id));
	else if (str_cmp(name, "USR2") == 0)
		return (sig_parse_name_set(SIGUSR2, SIGUSR2_ID, out_signo, out_sig_id));
	return (error(ERR_VAR_INVALID_NAME));
}

static inline t_error	sig_parse_name_2(
							const char *name,
							int *out_signo,
							t_sig_id *out_sig_id)
{
	if (str_cmp(name, "TERM") == 0 || str_cmp(name, "15") == 0)
		return (sig_parse_name_set(SIGTERM, SIGTERM_ID, out_signo, out_sig_id));
	else if (str_cmp(name, "URG") == 0)
		return (sig_parse_name_set(SIGURG, SIGURG_ID, out_signo, out_sig_id));
	else if (str_cmp(name, "TSTP") == 0)
		return (sig_parse_name_set(SIGTSTP, SIGTSTP_ID, out_signo, out_sig_id));
	else if (str_cmp(name, "CONT") == 0)
		return (sig_parse_name_set(SIGCONT, SIGCONT_ID, out_signo, out_sig_id));
	else if (str_cmp(name, "CHLD") == 0)
		return (sig_parse_name_set(SIGCHLD, SIGCHLD_ID, out_signo, out_sig_id));
	else if (str_cmp(name, "TTIN") == 0)
		return (sig_parse_name_set(SIGTTIN, SIGTTIN_ID, out_signo, out_sig_id));
	else if (str_cmp(name, "TTOU") == 0)
		return (sig_parse_name_set(SIGTTOU, SIGTTOU_ID, out_signo, out_sig_id));
	else if (str_cmp(name, "XCPU") == 0)
		return (sig_parse_name_set(SIGXCPU, SIGXCPU_ID, out_signo, out_sig_id));
	else if (str_cmp(name, "XFSZ") == 0)
		return (sig_parse_name_set(SIGXFSZ, SIGXFSZ_ID, out_signo, out_sig_id));
	else if (str_cmp(name, "VTALRM") == 0)
		return (sig_parse_name_set(SIGVTALRM, SIGVTALRM_ID, out_signo,
				out_sig_id));
	else if (str_cmp(name, "WINCH") == 0)
		return (sig_parse_name_set(SIGWINCH, SIGWINCH_ID, out_signo,
				out_sig_id));
	return (sig_parse_name_3(name, out_signo, out_sig_id));
}

t_error	sig_parse_name(
			const char *name,
			int *out_signo,
			t_sig_id *out_sig_id)
{
	if (str_cmp(name, "HUP") == 0 || str_cmp(name, "1") == 0)
		return (sig_parse_name_set(SIGHUP, SIGHUP_ID, out_signo, out_sig_id));
	else if (str_cmp(name, "INT") == 0 || str_cmp(name, "2") == 0)
		return (sig_parse_name_set(SIGINT, SIGINT_ID, out_signo, out_sig_id));
	else if (str_cmp(name, "QUIT") == 0 || str_cmp(name, "3") == 0)
		return (sig_parse_name_set(SIGQUIT, SIGQUIT_ID, out_signo, out_sig_id));
	else if (str_cmp(name, "ILL") == 0)
		return (sig_parse_name_set(SIGILL, SIGILL_ID, out_signo, out_sig_id));
	else if (str_cmp(name, "TRAP") == 0)
		return (sig_parse_name_set(SIGTRAP, SIGTRAP_ID, out_signo, out_sig_id));
	else if (str_cmp(name, "ABRT") == 0 || str_cmp(name, "6") == 0)
		return (sig_parse_name_set(SIGABRT, SIGABRT_ID, out_signo, out_sig_id));
	else if (str_cmp(name, "FPE") == 0)
		return (sig_parse_name_set(SIGFPE, SIGFPE_ID, out_signo, out_sig_id));
	else if (str_cmp(name, "BUS") == 0)
		return (sig_parse_name_set(SIGBUS, SIGBUS_ID, out_signo, out_sig_id));
	else if (str_cmp(name, "SEGV") == 0)
		return (sig_parse_name_set(SIGSEGV, SIGSEGV_ID, out_signo, out_sig_id));
	else if (str_cmp(name, "SYS") == 0)
		return (sig_parse_name_set(SIGSYS, SIGSYS_ID, out_signo, out_sig_id));
	else if (str_cmp(name, "PIPE") == 0)
		return (sig_parse_name_set(SIGPIPE, SIGPIPE_ID, out_signo, out_sig_id));
	else if (str_cmp(name, "ALRM") == 0 || str_cmp(name, "14") == 0)
		return (sig_parse_name_set(SIGALRM, SIGALRM_ID, out_signo, out_sig_id));
	return (sig_parse_name_2(name, out_signo, out_sig_id));
}
