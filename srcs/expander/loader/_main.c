#include <stdlib.h>
#include "loader_.h"
#include "loader_context_.h"

static t_error	loader_char(t_loader *state)
{
	if (is_char_escaped(state))
	{
		if (loader_consume(state, false).type)
			return (state->err);
		return (loader_consume(state, true));
	}
	else
		return (loader_consume(state, false));
}

static t_error	loader_substitution(t_loader *state)
{
	t_context	outer_local;

	if (loader_push_context(state).type)
		return (state->err);
	outer_local = state->local_quoting;
	if (loader_char(state).type)
		return (state->err);
	state->local_quoting = CONTEXT_NONE;
	while (state->i < state->context_item->end)
	{
		if (is_substitution_start(state))
		{
			if (loader_substitution(state).type)
				return (state->err);
		}
		else if (is_quoting_start(state))
		{
			if (loader_quoted(state).type)
				return (state->err);
		}
		else if (loader_char(state).type)
			return (state->err);
	}
	state->local_quoting = outer_local;
	return (loader_pop_context(state));
}

t_error	loader_quoted(t_loader *loader)
{
	t_context_stack_item	*item;
	t_context				previous_quoting;
	t_context				previous_local;

	loader->err = context_stack_fpop(&loader->stack, &item);
	if (loader->err.type)
		return (loader->err);
	previous_quoting = loader->quoting;
	previous_local = loader->local_quoting;
	loader->quoting = item->context;
	loader->local_quoting = item->context;
	while (loader->i <= item->end && !loader->err.type)
	{

		if (is_substitution_start(loader))
			loader_substitution(loader);
		else if (is_quoting_start(loader))
			loader_quoted(loader);
		else
			loader_char(loader);
	}
	loader->quoting = previous_quoting;
	loader->local_quoting = previous_local;
	return (free(item), loader->err);
}

t_error	loader_prepare_word(t_loader *loader)
{
	loader->quoting = CONTEXT_NONE;
	loader->local_quoting = CONTEXT_NONE;
	if (is_substitution_start(loader))
		loader_substitution(loader);
	else if (is_char_escaped(loader))
	{
		loader_consume(loader, false);
		if (loader->err.type)
			return (loader->err);
		loader_consume(loader, true);
		if (loader->err.type)
			return (loader->err);
	}
	else if (is_quoting_start(loader))
		loader_quoted(loader);
	else
		loader_consume(loader, false);
	return (loader->err);
}
