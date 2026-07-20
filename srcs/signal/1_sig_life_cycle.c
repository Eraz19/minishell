#include "sig.h"
#include "sig_priv.h"
#include "sig_action.h"
#include <stdlib.h>

t_error	sig_init_subshell(bool async_no_job_ctrl)
{
	t_sig_state		*sig_state;
	t_sig_id		sig_id;
	t_sig_action	*action;
	t_error			err;

	sig_state = &g_signals.state;
	sig_id = 0;
	err.type = ERR_NO;
	while (sig_id < SIG_ID_COUNT)
	{
		action = &sig_state->actions[sig_id];
		if (async_no_job_ctrl && (sig_id == SIGINT_ID || sig_id == SIGQUIT_ID))
			err = sig_install_ignore(action, sig_id_to_no(sig_id));
		else if (action->type != SIG_IGNORED)
			err = sig_install_default(action, sig_id_to_no(sig_id));
		if (err.type)
			return (err);
		sig_id++;
	}
	if (sig_state->exit_action.type != SIG_IGNORED)
	{
		string_free(&sig_state->exit_action.cmd);
		sig_state->exit_action.type = SIG_DEFAULT;
	}
	return (error(ERR_NO));
}

void	sig_clear(void)
{
	// no-op: no allocation and signals must remain tracked
	return ;
}

void	sig_free(void)
{
	t_sig_state	*sig_state;
	size_t		i;

	sig_state = &g_signals.state;
	i = 0;
	while (i < SIG_ID_COUNT)
	{
		sig_action_free(&sig_state->actions[i]);
		i++;
	}
	sig_action_free(&sig_state->exit_action);
	g_signals = (t_signals){0};
}
