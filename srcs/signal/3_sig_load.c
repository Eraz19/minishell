#include "sig.h"
#include "sig_priv.h"
#include "params.h"
#include "options.h"

static inline t_error	sig_err(t_error_type type, const char *message)
{
	return (error_print(error(type), "signal", message, NULL, NULL));
}

static inline t_error	sig_load_ignored_on_entry(t_sig_state *sig_state)
{
	bool				interactive;
	size_t				i;
	int					signo;
	struct sigaction	sa;
	t_error				err;

	err = option_is_active(OPT_INTERACTIVE, &interactive);
	if (err.type || interactive == true)
		return (err);
	i = 0;
	while (i < SIG_ID_COUNT)
	{
		signo = sig_id_to_no((t_sig_id)i);
		if (signo < 0)
			return (sig_err(ERR_INTERNAL, "unrecognized sig_id"));
		if (sigaction(signo, NULL, &sa) != 0)
			return (sig_err(ERR_LIBC, "unable to read sigaction"));
		if (sa.sa_handler == SIG_IGN)
		{
			sig_state->ignored_on_entry[i] = true;
			sig_state->actions[i].type = SIG_IGNORED;
		}
		i++;
	}
	return (error(ERR_NO));
}

static inline t_error	sig_ignore_default_signals_2(
							t_sig_state *sig_state,
							struct sigaction *sa)
{
#ifdef SIGTTIN
	if (sigaction(SIGTTIN, sa, NULL) != 0)
		return (sig_err(ERR_LIBC, "unable to ignore SIGTTIN"));
	sig_state->actions[SIGTTIN_ID].type = SIG_IGNORED;
#endif
#ifdef SIGTTOU
	if (sigaction(SIGTTOU, sa, NULL) != 0)
		return (sig_err(ERR_LIBC, "unable to ignore SIGTTOU"));
	sig_state->actions[SIGTTOU_ID].type = SIG_IGNORED;
#endif
#ifdef SIGTSTP
	if (sigaction(SIGTSTP, sa, NULL) != 0)
		return (sig_err(ERR_LIBC, "unable to ignore SIGTSTP"));
	sig_state->actions[SIGTSTP_ID].type = SIG_IGNORED;
#endif
	return (error(ERR_NO));
}

static inline t_error	sig_ignore_default_signals(t_sig_state *sig_state)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
#ifdef SIGQUIT
	if (sigaction(SIGQUIT, &sa, NULL) != 0)
		return (sig_err(ERR_LIBC, "unable to ignore SIGQUIT"));
	sig_state->actions[SIGQUIT_ID].type = SIG_IGNORED;
#endif
#ifdef SIGTERM
	if (sigaction(SIGTERM, &sa, NULL) != 0)
		return (sig_err(ERR_LIBC, "unable to ignore SIGTERM"));
	sig_state->actions[SIGTERM_ID].type = SIG_IGNORED;
#endif
	return (sig_ignore_default_signals_2(sig_state, &sa));
}

t_error	sig_load(t_params *params)
{
	t_sig_state	*sig_state;
	t_error		err;

	sig_state =&g_signals.state;
	err = sig_load_ignored_on_entry(sig_state);
	if (err.type)
		return (err);
	if (option_is_active_in(params->options, OPT_INTERACTIVE) == true)
	{
		err = sig_ignore_default_signals(sig_state);
		if (err.type)
			return (err);
	}
	return (sig_install_shell_default_sigint(&sig_state->actions[SIGINT_ID]));
}
