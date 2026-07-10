#include "param_braced_.h"

static t_error	braced_body_len(t_expander *expander, size_t *body_len)
{
	t_word_item	item;

	expander->err = word_get(&item, &expander->word, 0);
	if (expander->err.type)
		return (expander->err);
	if (item.opt.context_len < 3)
		return (expander->err = error(ERR_INCOHERENT_STATE));
	*body_len = item.opt.context_len - 3;
	return (expander->err);
}

t_error	expand_braced(t_expander *expander)
{
	size_t		body_len;
	t_word_item	item;

	expander->err = braced_body_len(expander, &body_len);
	if (expander->err.type)
		return (expander->err);
	expander->err = word_remove(&expander->word, 0, 2);
	if (expander->err.type)
		return (expander->err);
	if (body_len == 0)
	{
		expander->err = error_print(error(ERR_PARAM_BAD_SUBSTITUTION),
				"expander", "${}", NULL, NULL);
		return (expander->err);
	}
	expander->err = word_get(&item, &expander->word, 0);
	if (expander->err.type)
		return (expander->err);
	if (item.c == '#')
		return (expand_braced_length(expander, body_len));
	if (item.c == '@' || item.c == '*')
		return (expand_braced_positional(expander, body_len));
	return (expand_braced_param(expander, body_len));
}
