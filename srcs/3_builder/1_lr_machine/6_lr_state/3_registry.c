#include "lr_state.h"

bool	lr_state_find_id(t_vector *lr_states, t_lr_state *lr_state, size_t *id)
{
	size_t		i;
	t_lr_state	*current_lr_state;

	i = 0;
	while (i < lr_states->len)
	{
		current_lr_state = &((t_lr_state *)lr_states->data)[i];
		if (lr_state_equal(current_lr_state, lr_state))
		{
			if (id)
				*id = i;
			return (true);
		}
		i++;
	}
	return (false);
}

t_error	lr_state_add(t_vector *lr_states, t_lr_state *lr_state, bool *did_add)
{
	if (lr_state_find_id(lr_states, lr_state, NULL))
		return (ERR_NO);
	if (!vector_push(lr_states, lr_state))
		return (ERR_LIBC);
	if (did_add)
		*did_add = true;
	return (ERR_NO);
}
