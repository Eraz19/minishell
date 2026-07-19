#include "sig.h"

bool	sig_has_pending_trap(int *out_signo)
{
	t_sig_id		sig_id;

	if (g_signals.has_pending == false)
		return (false);
	sig_id = 0;
	while (sig_id < SIG_ID_COUNT)
	{
		if (g_signals.pending[sig_id] == true
			&& g_signals.state.actions[sig_id].type == SIG_TRAPPED)
			return (*out_signo = sig_id_to_no(sig_id), true);
		sig_id++;
	}
	return (false);
}
