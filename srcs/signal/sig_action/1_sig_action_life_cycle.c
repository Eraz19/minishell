#include "sig_action.h"

void	sig_action_init(t_sig_action *action)
{
	action->type = SIG_DEFAULT;
	(void)string_init(&action->cmd, 0, NULL, 0);
}

void	sig_action_free(t_sig_action *action)
{
	action->type = SIG_DEFAULT;
	string_free(&action->cmd);
}
