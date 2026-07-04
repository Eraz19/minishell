#include "quote_removal_context_.h"

static t_error	context_escape(
	t_expander *expander,
	t_context_args args,
	t_word_item item)
{
	t_word_item	escaped_item;

	expander->err = word_fpop(&escaped_item, args.word);
	if (expander->err.type)
		return (expander->err);
	if (!args.is_in_whitelist(escaped_item.c))
	{
		expander->err = word_push(args.word_expanded, item);
		if (expander->err.type)
			return (expander->err);
	}
	return (expander->err = word_push(args.word_expanded, escaped_item));
}

static t_error	context_end(t_expander *expander, t_context_args args)
{
	t_word_item_opt	opt;
	t_word_item		item;

	if (args.word_expanded->len != 0)
		return (expander->err);
	opt.context = args.context;
	
	item = word_item_init('\0', opt);
	return (expander->err = word_push(args.word_expanded, item));
}

t_error	context_scan(t_expander *expander, t_context_args args)
{
	t_word_item	item;

	while (true)
	{
		expander->err = word_fpop(&item, args.word);
		if (expander->err.type)
			return (expander->err);
		if (args.is_end != NULL && args.is_end(item.c, NULL))
			return (context_end(expander, args));
		else if (item.c == '\\' && args.is_in_whitelist != NULL)
		{
			expander->err = context_escape(expander, args, item);
			if (expander->err.type)
				return (expander->err);
		}
		else
		{
			expander->err = word_push(args.word_expanded, item);
			if (expander->err.type)
				return (expander->err);
		}
	}
}
