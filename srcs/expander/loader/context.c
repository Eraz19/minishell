#include <stdlib.h>
#include "expander_loader_.h"

static t_error	expander_loader_char(t_expander_loader *state)
{
	if (is_char_escaped(state))
	{
		if (expander_loader_consume(state, 1, false).type)
			return (state->err);
		return (expander_loader_consume(state, 1, true));
	}
	else
		return (expander_loader_consume(state, 1, false));
}

static t_error	expander_loader_context(t_expander_loader *state)
{
	if (is_substitution_start(state))
		return (expander_loader_substitution(state));
	else if (is_quoting_start(state))
		return (expander_loader_quoted(state));
	else
		return (expander_loader_char(state));
}

t_error	expander_loader_substitution(t_expander_loader *state)
{
	if (expander_loader_push_context(state).type)
		return (state->err);
	while (state->i < state->context_item->end)
	{
		if (state->i != state->context_item->start)
		{
			if (is_substitution_start(state))
				return (expander_loader_substitution(state));
			else if (is_quoting_start(state))
			{
				if (expander_loader_quoted(state).type)
					return (state->err);
			}
			else if (expander_loader_char(state).type)
				return (state->err);
		}
		else if (expander_loader_char(state).type)
			return (state->err);
	}
	return (expander_loader_pop_context(state));
}

t_error	expander_loader_quoted(t_expander_loader *state)
{
	t_context_stack_item	*item;
	t_context				previous_quoting;

	state->err = context_stack_fpop(&state->stack, &item);
	if (state->err.type)
		return (state->err);
	previous_quoting = state->quoting;
	state->quoting = item->context;
	while (state->i < item->end && !state->err.type)
		expander_loader_context(state);
	state->quoting = previous_quoting;
	return (free(item), state->err);
}
