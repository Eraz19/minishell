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
