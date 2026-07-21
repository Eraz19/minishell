#include "sig.h"
#include "sig_priv.h"
#include "sig_action.h"
#include <stdlib.h>

static inline t_error	sig_init_subshell_action(
							t_sig_id sig_id,
							bool async_no_job_ctrl)
{
	t_sig_action	*action;

	action = &g_signals.state.actions[sig_id];
	if (async_no_job_ctrl && (sig_id == SIGINT_ID || sig_id == SIGQUIT_ID))
		return (sig_install_ignore(action, sig_id_to_no(sig_id)));
	else if (action->type != SIG_IGNORED)
		return (sig_install_default(action, sig_id_to_no(sig_id)));
	return (error(ERR_NO));
}

t_error	sig_init_subshell(bool async_no_job_ctrl)
{
	t_sig_id		sig_id;
	t_error			err;

	sig_id = 0;
	err.type = ERR_NO;
	sig_snapshot();
	g_signals.trap_with_operand_has_been_executed = false;
	while (sig_id < SIG_ID_COUNT)
	{
		err = sig_init_subshell_action(sig_id, async_no_job_ctrl);
		if (err.type)
			return (err);
		sig_id++;
	}
	if (g_signals.state.exit_action.type != SIG_IGNORED)
	{
		string_free(&g_signals.state.exit_action.cmd);
		g_signals.state.exit_action.type = SIG_DEFAULT;
	}
	return (err);
}

// no-op: no allocation and signals must remain tracked
void	sig_clear(void)
{
	return ;
}

void	sig_free(void)
{
	size_t	i;

	i = 0;
	while (i < SIG_ID_COUNT)
	{
		sig_action_free(&g_signals.state.actions[i]);
		sig_action_free(&g_signals.snapshot.actions[i]);
		i++;
	}
	sig_action_free(&g_signals.state.exit_action);
	sig_action_free(&g_signals.snapshot.exit_action);
	g_signals = (t_signals){0};
}
