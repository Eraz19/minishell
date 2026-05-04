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

void	lr_state_free(t_lr_state *lr_state)
{
	vector_free(lr_state);
}

void	lr_state_table_free(t_lr_state *lr_states)
{
	size_t	i;

	i = 0;
	while (i < lr_states->len)
	{
		lr_state_free(&((t_lr_state *)lr_states->data)[i]);
		i++;
	}
	vector_free(lr_states);
}
