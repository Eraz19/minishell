#include "sig.h"
#include "sig_priv.h"
#include "sig_action.h"
#include <stdlib.h>

t_error	sig_init_subshell(void)
{
	t_sig_state		*sig_state;
	size_t			i;
	t_sig_action	*action;
	t_error			err;

	sig_state = &g_signals.state;
	i = 0;
	while (i < SIG_ID_COUNT)
	{
		action = &sig_state->actions[(t_sig_id)i];
		if (action->type == SIG_TRAPPED)
		{
			err = sig_install_default(action, sig_id_to_no((t_sig_id)i));
			if (err.type)
				return (err);
		}
		i++;
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
