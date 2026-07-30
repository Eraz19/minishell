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

t_error	drop_quoted_null_at(t_expander *expander)
{
	t_word_item	open;
	t_word_item	close;

	if (expander->word_exp.len == 0 || expander->word.len < 2)
		return (expander->err);
	expander->err = word_get(&open, &expander->word_exp,
			expander->word_exp.len - 1);
	if (expander->err.type)
		return (expander->err);
	expander->err = word_get(&close, &expander->word, 1);
	if (expander->err.type)
		return (expander->err);
	if (open.c != '"' || open.opt.is_expand_res || open.opt.escaped
		|| close.c != '"' || close.opt.is_expand_res || close.opt.escaped)
		return (expander->err);
	expander->err = word_remove(&expander->word_exp,
			expander->word_exp.len - 1, 1);
	if (expander->err.type)
		return (expander->err);
	return (expander->err = word_remove(&expander->word, 1, 1));
}

t_word_item	simple_dquote_item(t_word_item_opt opt)
{
	t_word_item	item;

	item.c = '"';
	item.opt = opt;
	item.opt.is_expand_res = false;
	return (item);
}
