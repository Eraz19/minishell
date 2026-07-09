#include "param_braced_.h"
#include "param_unbraced_.h"

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

t_error	param_expansion(t_expander *expander)
{
	t_word_item	item;

	expander->err = word_get(&item, &expander->word, 1);
	if (expander->err.type)
		return (expander->err);
	if (item.c == '{')
		return (expand_braced(expander));
	else
		return (expand_unbraced(expander));
}
