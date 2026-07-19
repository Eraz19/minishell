#include "sig_id_to_no_priv.h"

static inline int	sig_id_to_no_2_e(t_sig_id sig_id)
{
#ifdef SIGFREEZE
	if (sig_id == SIGFREEZE_ID)
		return (SIGFREEZE);
#endif
#ifdef SIGTHAW
	if (sig_id == SIGTHAW_ID)
		return (SIGTHAW);
#endif
#ifdef SIGCANCEL
	if (sig_id == SIGCANCEL_ID)
		return (SIGCANCEL);
#endif
	(void)sig_id;
	return (-1);
}

static inline int	sig_id_to_no_2_d(t_sig_id sig_id)
{
#ifdef SIGSTKFLT
	if (sig_id == SIGSTKFLT_ID)
		return (SIGSTKFLT);
#endif
#ifdef SIGUNUSED
	if (sig_id == SIGUNUSED_ID)
		return (SIGUNUSED);
#endif
#ifdef SIGTHR
	if (sig_id == SIGTHR_ID)
		return (SIGTHR);
#endif
#ifdef SIGLIBRT
	if (sig_id == SIGLIBRT_ID)
		return (SIGLIBRT);
#endif
#ifdef SIGWAITING
	if (sig_id == SIGWAITING_ID)
		return (SIGWAITING);
#endif
#ifdef SIGLWP
	if (sig_id == SIGLWP_ID)
		return (SIGLWP);
#endif
	return (sig_id_to_no_2_e(sig_id));
}

static inline int	sig_id_to_no_2_c(t_sig_id sig_id)
{
#ifdef SIGUSR1
	if (sig_id == SIGUSR1_ID)
		return (SIGUSR1);
#endif
#ifdef SIGUSR2
	if (sig_id == SIGUSR2_ID)
		return (SIGUSR2);
#endif
#ifdef SIGPOLL
	if (sig_id == SIGPOLL_ID)
		return (SIGPOLL);
#endif
#ifdef SIGCLD
	if (sig_id == SIGCLD_ID)
		return (SIGCLD);
#endif
#ifdef SIGPWR
	if (sig_id == SIGPWR_ID)
		return (SIGPWR);
#endif
#ifdef SIGLOST
	if (sig_id == SIGLOST_ID)
		return (SIGLOST);
#endif
	return (sig_id_to_no_2_d(sig_id));
}

static inline int	sig_id_to_no_2_b(t_sig_id sig_id)
{
#ifdef SIGXCPU
	if (sig_id == SIGXCPU_ID)
		return (SIGXCPU);
#endif
#ifdef SIGXFSZ
	if (sig_id == SIGXFSZ_ID)
		return (SIGXFSZ);
#endif
#ifdef SIGVTALRM
	if (sig_id == SIGVTALRM_ID)
		return (SIGVTALRM);
#endif
#ifdef SIGPROF
	if (sig_id == SIGPROF_ID)
		return (SIGPROF);
#endif
#ifdef SIGWINCH
	if (sig_id == SIGWINCH_ID)
		return (SIGWINCH);
#endif
#ifdef SIGINFO
	if (sig_id == SIGINFO_ID)
		return (SIGINFO);
#endif
	return (sig_id_to_no_2_c(sig_id));
}

int	sig_id_to_no_2(t_sig_id sig_id)
{
#ifdef SIGTSTP
	if (sig_id == SIGTSTP_ID)
		return (SIGTSTP);
#endif
#ifdef SIGCONT
	if (sig_id == SIGCONT_ID)
		return (SIGCONT);
#endif
#ifdef SIGCHLD
	if (sig_id == SIGCHLD_ID)
		return (SIGCHLD);
#endif
#ifdef SIGTTIN
	if (sig_id == SIGTTIN_ID)
		return (SIGTTIN);
#endif
#ifdef SIGTTOU
	if (sig_id == SIGTTOU_ID)
		return (SIGTTOU);
#endif
#ifdef SIGIO
	if (sig_id == SIGIO_ID)
		return (SIGIO);
#endif
	return (sig_id_to_no_2_b(sig_id));
}
