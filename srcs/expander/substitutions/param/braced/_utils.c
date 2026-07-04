#include "params.h"
#include "param_braced_.h"

static t_word_item_opt	braced_result_opt(t_word_item_opt in)
{
	in.context = CONTEXT_NONE;
	in.escaped = false;
	in.is_expand_res = true;
	return (in);
}

t_error	braced_push_value(
	t_expander *expander,
	const t_string *val,
	t_word_item_opt opt)
{
	t_word	word_exp;

	expander->err = from_str(&word_exp, val, braced_result_opt(opt));
	if (expander->err.type)
		return (expander->err);
	if (!vector_merge(&expander->word_exp, &word_exp, expander->word_exp.len))
		expander->err = error_sys();
	return (word_free(&word_exp), expander->err);
}

t_error	braced_expect_close(t_expander *expander)
{
	t_word_item	item;

	expander->err = word_get(&item, &expander->word, 0);
	if (expander->err.type)
		return (expander->err);
	if (item.c != '}')
		return (expander->err = error(ERR_PARAM_BAD_SUBSTITUTION));
	return (expander->err);
}

t_error	braced_lookup(t_expander *expander, const t_string *name, t_string *out)
{
	expander->err = params_get_from_const(name->data, out);
	if (expander->err.type == ERR_VAR_NOT_FOUND)
	{
		if (!string_init(out, 0, "", -1))
			return (expander->err = error_sys());
		return (expander->err = error(ERR_NO));
	}
	if (expander->err.type)
		return (expander->err);
	if (out->data == NULL && !string_init(out, 0, "", -1))
		return (expander->err = error_sys());
	return (expander->err);
}

t_error	braced_finish(
	t_expander *expander,
	t_string *value,
	t_word_item_opt opt)
{
	expander->err = braced_push_value(expander, value, opt);
	string_free(value);
	if (expander->err.type)
		return (expander->err);
	return (expander->err = word_remove(&expander->word, 0, 1));
}
