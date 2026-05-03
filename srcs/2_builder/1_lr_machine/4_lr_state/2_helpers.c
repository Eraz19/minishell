#include "lr_state.h"
#include "rule_state.h"

static bool	lr_state_contains_rule_state(t_lr_state *lr_state, t_rule_state rule_state)
{
	size_t			i;
	t_rule_state	*items;

	i = 0;
	items = (t_rule_state *)lr_state->data;
	while (i < lr_state->len)
	{
		if (rule_state_equal(items[i], rule_state))
			return (true);
		i++;
	}
	return (false);
}

bool	lr_state_equal(t_lr_state *a, t_lr_state *b)
{
	size_t			i;
	t_rule_state	*items;

	if (a->len != b->len)
		return (false);
	items = (t_rule_state *)a->data;
	i = 0;
	while (i < a->len)
	{
		if (!lr_state_contains_rule_state(b, items[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	lr_state_add_rule_state(t_lr_state *lr_state, t_rule_state rule_state, bool *did_add)
{
	if (lr_state_contains_rule_state(lr_state, rule_state))
		return (true);
	if (!vector_push(lr_state, &rule_state))
		return (false);
	if (did_add)
		*did_add = true;
	return (true);
}

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

bool	lr_state_add(t_vector *lr_states, t_lr_state *lr_state, bool *did_add)
{
	if (lr_state_find_id(lr_states, lr_state, NULL))
		return (true);
	if (!vector_push(lr_states, lr_state))
		return (false);
	if (did_add)
		*did_add = true;
	return (true);
}
