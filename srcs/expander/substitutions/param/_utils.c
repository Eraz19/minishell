#include "expander_.h"

size_t	scan_param_run(t_expander *expander, size_t i, bool digits)
{
	t_word_item	item;

	while (i < expander->word.len)
	{
		if (word_get(&item, &expander->word, i).type)
			break ;
		if (digits && !ft_isdigit(item.c))
			break ;
		if (!digits && item.c != '_' && !ft_isalnum(item.c))
			break ;
		i++;
	}
	return (i);
}

t_error	get_param_name(t_expander *expander, t_string *param_name, bool braced)
{
	size_t		i;
	t_word_item	item;

	expander->err = word_get(&item, &expander->word, 0);
	if (expander->err.type)
		return (expander->err);
	i = 1;
	if (ft_isalpha(item.c) || item.c == '_')
		i = scan_param_run(expander, 1, false);
	else if (braced && ft_isdigit(item.c))
		i = scan_param_run(expander, 1, true);
	expander->err = to_str(param_name, &expander->word, 0, i);
	if (expander->err.type)
		return (expander->err);
	return (expander->err = word_remove(&expander->word, 0, i));
}

bool	is_valid_param(t_word_item *item)
{
	if (item->c == '?'
		|| item->c == '#'
		|| item->c == '-'
		|| item->c == '*'
		|| item->c == '$'
		|| item->c == '!'
		|| item->c == '@'
		|| item->c == '_'
		|| ft_isalnum(item->c))
		return (true);
	return (false);
}

bool	context_prevent_param_expansion(t_word_item *item)
{
	t_context	context;
	bool		is_valid_quoting;
	bool		is_valid_context;

	context = item->opt.context;
	is_valid_context = context == CONTEXT_NONE || context == CONTEXT_PARAM;
	is_valid_quoting = item->opt.quoted != CONTEXT_SQUOTE && !item->opt.escaped;
	return (!is_valid_context || !is_valid_quoting);
}

bool	is_param_expansion(t_expander *expander, t_word_item *current_item)
{
	t_error		err;
	t_word_item	item;

	if (!flag_is_active((uint)expander->flags, EXP_PARAM))
		return (false);
	if (current_item->c != '$' || context_prevent_param_expansion(current_item))
		return (false);
	err = word_get(&item, &expander->word, 1);
	if (err.type)
		return (false);
	if (item.c == '{')
		return (true);
	return (is_valid_param(&item));
}
