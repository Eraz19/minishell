#include "lr_state.h"

void	lr_state_init(t_lr_state *lr_state)
{
	vector_init(lr_state, sizeof(t_rule_state), 0);
}

void	lr_state_free(t_lr_state *lr_state)
{
	vector_free(lr_state);
}
