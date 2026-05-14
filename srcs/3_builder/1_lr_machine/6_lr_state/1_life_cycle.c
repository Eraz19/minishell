#include "lr_state.h"
#include <stdlib.h>

void	lr_state_init(t_lr_state *lr_state)
{
	vector_init(lr_state, sizeof(t_rule_state), 0);
}

void	lr_state_table_init(t_lr_state *lr_states)
{
	vector_init(lr_states, sizeof(t_lr_state), 0);
}

void	lr_state_free(void *lr_state)
{
	vector_free((t_lr_state *)lr_state, NULL);
}

void	lr_state_table_free(t_lr_state *lr_states)
{
	vector_free(lr_states, lr_state_free);
}
