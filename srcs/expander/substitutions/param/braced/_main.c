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

t_error	expand_braced_dispatch(t_expander *expander, size_t body_len)
{
	t_word_item	item;

	expander->err = word_get(&item, &expander->word, 0);
	if (expander->err.type)
		return (expander->err);
	if (item.c == '#')
		return (expand_braced_length(expander, body_len));
	if (item.c == '@' || item.c == '*')
		return (expand_braced_positional(expander, body_len));
	return (expand_braced_param(expander, body_len));
}

t_error	expand_braced(t_expander *expander)
{
	t_string	body;
	size_t		body_len;

	expander->err = braced_body_len(expander, &body_len);
	if (expander->err.type)
		return (expander->err);
	expander->err = to_str(&body, &expander->word, 0, body_len + 3);
	if (expander->err.type)
		return (expander->err);
	expander->err = word_remove(&expander->word, 0, 2);
	if (expander->err.type)
		return (string_free(&body), expander->err);
	if (body_len == 0)
	{
		expander->err = error_print(error(ERR_PARAM_BAD_SUBSTITUTION),
				"expander", body.data, NULL, NULL);
		return (string_free(&body), expander->err);
	}
	expander->err = expand_braced_dispatch(expander, body_len);
	if (expander->err.type == ERR_PARAM_BAD_SUBSTITUTION)
		expander->err = error_print(expander->err,
				"expander", body.data, NULL, NULL);
	return (string_free(&body), expander->err);
}
