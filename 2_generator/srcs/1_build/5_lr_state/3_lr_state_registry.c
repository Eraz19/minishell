#include "generator_lr_state.h"
#include "generator_lr_state_priv.h"
#include <stdio.h>

bool	lr_state_find_id(
			const t_vector *lr_states,
			const t_lr_state *lr_state,
			size_t *id)
{
	size_t				i;
	const t_lr_state	*current_lr_state;

	i = 0;
	while (i < lr_states->len)
	{
		current_lr_state = &((const t_lr_state *)lr_states->data)[i];
		if (lr_state_equal(current_lr_state, lr_state))
		{
			if (id != NULL)
				*id = i;
			return (true);
		}
		i++;
	}
	return (false);
}

bool	lr_state_add(
			t_vector *lr_states,
			const t_lr_state *lr_state,
			bool *did_add)
{
	if (lr_state_find_id(lr_states, lr_state, NULL))
		return (true);
	if (!vector_push(lr_states, lr_state))
		return (perror("generator"), false);
	if (did_add)
		*did_add = true;
	return (true);
}
