#include "lr_state.h"
#include "rule_state.h"

bool	lr_state_init(t_lr_state *lr_state)
{
	return (vector_init(lr_state, sizeof(t_rule_state), LR_STATE_INITIAL_CAP));
}

bool	lr_state_contains(t_lr_state *lr_state, t_rule_state rule_state)
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
		if (!lr_state_contains(b, items[i]))
			return (false);
		i++;
	}
	return (true);
}

void	lr_state_free(t_lr_state *lr_state)
{
	vector_free(lr_state);
}
