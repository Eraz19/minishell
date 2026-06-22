#include "expander_loader_.h"

static t_error	expander_loader_char(t_expander_loader *state)
{
	if (is_char_escaped(state))
	{
		if (expander_loader_consume(state, 1).type)
			return (state->err);
	}
	return (expander_loader_consume(state, 1));
}

static t_error	expander_loader_context(t_expander_loader *state)
{
	if (is_substitution_start(state))
		return (expander_loader_substitution(state));
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
	char	current;

	if (state->quoting != DOLLAR_SQUOTE)
		expander_loader_consume(state, 1);
	else
		expander_loader_consume(state, 2);
	if (state->err.type)
		return (state->err);
	current = state->word[state->i];
	while (current != '\0' && !is_quoting_ending(current, state->quoting))
	{
		if (expander_loader_context(state).type)
			return (state->err);
		current = state->word[state->i];
	}
	if (state->word[state->i] == '\0')
		return (state->err);
	return (expander_loader_consume(state, 1));
}
