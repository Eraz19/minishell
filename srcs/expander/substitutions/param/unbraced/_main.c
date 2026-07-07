#include "params.h" 
#include "param_expansion_.h"

t_error	expand_positional_single(t_expander *expander, t_word_item_opt opt)
{
	t_word		word_exp;
	t_string	param_exp;
	t_string	param_name;

	expander->err = get_param_name(expander, &param_name, false);
	if (expander->err.type)
		return (expander->err);
	expander->err = params_get_from_const(param_name.data, &param_exp);
	if (expander->err.type != ERR_NO && expander->err.type != ERR_VAR_NOT_FOUND)
		return (string_free(&param_name), expander->err);
	expander->err = error(ERR_NO);
	if (param_exp.len == 0)
	{
		string_free(&param_exp);
		if (!string_init(&param_exp, 0, "", -1))
			return (string_free(&param_name), expander->err = error_sys());
	}
	string_free(&param_name);
	expander->err = from_str(&word_exp, &param_exp, opt);
	if (expander->err.type)
		return (string_free(&param_exp), expander->err);
	if (!vector_merge(&expander->word_exp, &word_exp, expander->word_exp.len))
		expander->err = error_sys();
	return (word_free(&word_exp), string_free(&param_exp), expander->err);
}

t_error	expand_positional_all(t_expander *expander)
{
	t_word_item	item;

	expander->err = word_get(&item, &expander->word, 0);
	if (expander->err.type != ERR_NO)
		return (expander->err);
	expander->err = emit_positionals(expander, item.c, item.opt);
	if (expander->err.type)
		return (expander->err);
	return (expander->err = word_remove(&expander->word, 0, 1));
}

t_error	expand_unbraced(t_expander *expander)
{
	t_word_item	item;

	expander->err = word_remove(&expander->word, 0, 1);
	if (expander->err.type)
		return (expander->err);
	expander->err = word_get(&item, &expander->word, 0);
	if (expander->err.type)
		return (expander->err);
	if (item.c == '@' || item.c == '*')
		return (expand_positional_all(expander));
	else
		return (expand_positional_single(expander, item.opt));
}
