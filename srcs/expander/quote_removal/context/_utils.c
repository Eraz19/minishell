#include "quote_removal_context_.h"

static t_error	context_escape(
	t_expander *state,
	t_context_args args,
	t_expander_word_item item)
{
	t_expander_word_item	escaped_item;

	state->err = expander_word_pop(args.word, &escaped_item);
	if (state->err.type)
		return (state->err);
	if (!args.is_in_whitelist(escaped_item.c))
	{
		state->err = expander_word_push(args.word_expanded, item);
		if (state->err.type)
			return (state->err);
	}
	return (state->err = expander_word_push(args.word_expanded, escaped_item));
}

static t_error	context_end(t_expander *state, t_context_args args)
{
	t_expander_word_item_opt	opt;
	t_expander_word_item		item;

	if (args.word_expanded->len != 0)
		return (state->err);
	opt.context = args.context;
	
	item = expander_word_item_init('\0', opt);
	return (state->err = expander_word_push(args.word_expanded, item));
}

t_error	context_scan(t_expander *state, t_context_args args)
{
	t_expander_word_item	item;

	while (true)
	{
		state->err = expander_word_pop(args.word, &item);
		if (state->err.type)
			return (state->err);
		if (args.is_end != NULL && args.is_end(item.c, NULL))
			return (context_end(state, args));
		else if (item.c == '\\' && args.is_in_whitelist != NULL)
		{
			state->err = context_escape(state, args, item);
			if (state->err.type)
				return (state->err);
		}
		else
		{
			state->err = expander_word_push(args.word_expanded, item);
			if (state->err.type)
				return (state->err);
		}
	}
}
