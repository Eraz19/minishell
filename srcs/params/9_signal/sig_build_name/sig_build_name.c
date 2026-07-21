#include "sig_priv.h"
#include "sig_build_name_priv.h"

static inline t_error	sig_build_name_1_c(t_sig_id sig_id, t_string *out_name)
{
#ifdef SIGSYS
	if (sig_id == SIGSYS_ID)
		return (sig_build_name_set("SYS", out_name));
#endif
#ifdef SIGPIPE
	if (sig_id == SIGPIPE_ID)
		return (sig_build_name_set("PIPE", out_name));
#endif
#ifdef SIGALRM
	if (sig_id == SIGALRM_ID)
		return (sig_build_name_set("ALRM", out_name));
#endif
#ifdef SIGTERM
	if (sig_id == SIGTERM_ID)
		return (sig_build_name_set("TERM", out_name));
#endif
#ifdef SIGURG
	if (sig_id == SIGURG_ID)
		return (sig_build_name_set("URG", out_name));
#endif
	return (sig_build_name_2(sig_id, out_name));
}

static inline t_error	sig_build_name_1_b(t_sig_id sig_id, t_string *out_name)
{
#ifdef SIGIOT
	if (sig_id == SIGIOT_ID)
		return (sig_build_name_set("IOT", out_name));
#endif
#ifdef SIGEMT
	if (sig_id == SIGEMT_ID)
		return (sig_build_name_set("EMT", out_name));
#endif
#ifdef SIGFPE
	if (sig_id == SIGFPE_ID)
		return (sig_build_name_set("FPE", out_name));
#endif
#ifdef SIGBUS
	if (sig_id == SIGBUS_ID)
		return (sig_build_name_set("BUS", out_name));
#endif
#ifdef SIGSEGV
	if (sig_id == SIGSEGV_ID)
		return (sig_build_name_set("SEGV", out_name));
#endif
	return (sig_build_name_1_c(sig_id, out_name));
}

t_error	sig_build_name(t_sig_id sig_id, t_string *out_name)
{
#ifdef SIGHUP
	if (sig_id == SIGHUP_ID)
		return (sig_build_name_set("HUP", out_name));
#endif
#ifdef SIGINT
	if (sig_id == SIGINT_ID)
		return (sig_build_name_set("INT", out_name));
#endif
#ifdef SIGQUIT
	if (sig_id == SIGQUIT_ID)
		return (sig_build_name_set("QUIT", out_name));
#endif
#ifdef SIGILL
	if (sig_id == SIGILL_ID)
		return (sig_build_name_set("ILL", out_name));
#endif
#ifdef SIGTRAP
	if (sig_id == SIGTRAP_ID)
		return (sig_build_name_set("TRAP", out_name));
#endif
#ifdef SIGABRT
	if (sig_id == SIGABRT_ID)
		return (sig_build_name_set("ABRT", out_name));
#endif
	return (sig_build_name_1_b(sig_id, out_name));
}
