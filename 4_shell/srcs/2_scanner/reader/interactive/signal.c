#include <signal.h>
#include "sig.h"
#include "env.h"
#include "reader_interactive_priv.h"

t_error	handle_reader_signals(bool *retry)
{
	int	signo;

	if (sig_int_is_pending() == true)
	{
		*retry = true;
		return (env_set_last_status(ERR_POSIX_SIGNAL_BASE_CODE + SIGINT));
	}
	else if (sig_has_pending_trap(&signo))
		return (env_set_last_status(ERR_POSIX_SIGNAL_BASE_CODE + signo));
	return (error(ERR_NO));
}
