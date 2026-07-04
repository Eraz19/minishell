#include "params.h"
#include "param_expansion_.h"

t_error	append_param_as_field(t_expander *expander, t_word word_exp, size_t i)
{
	if (i != 0)
	{
		expander->err = fields_push(&expander->fields_exp, expander->word_exp);
		if (expander->err.type)
			return (expander->err);
		word_init(&expander->word_exp);
	}
	if (!vector_merge(&expander->word_exp, &word_exp, expander->word_exp.len))
		return (expander->err = error_sys());
	return (expander->err);
}

t_error	join_param(t_string *out, const t_positionals *params, t_string *sep)
{
	size_t		i;
	t_error		err;
	t_string	param;

	i = 0;
	while (i < params->len)
	{
		param = ((t_string *)params->data)[i++];
		if (!string_append(out, &param))
			return (err = error_sys(), string_free(&param), err);
		if (i < params->len)
			if (!string_append(out, sep))
				return (err = error_sys(), string_free(&param), err);
	}
	return (error(ERR_NO));
}

t_error	expand_positional_star(t_expander *expander, t_word_item_opt opt)
{
	t_string			sep;
	const t_positionals	*params;
	t_word				word_exp;
	t_string			param_exp;

	expander->err = params_get_positionals(&params);
	if (expander->err.type)
		return (expander->err);
	if (!string_init(&sep, 0, expander->ifs.data, 1))
		return (expander->err = error_sys());
	string_init(&param_exp, 0, NULL, 0);
	expander->err = join_param(&param_exp, params, &sep);
	if (expander->err.type)
		return (string_free(&sep), string_free(&param_exp), expander->err);
	expander->err = from_str(&word_exp, &param_exp, opt);
	if (expander->err.type)
		return (string_free(&sep), string_free(&param_exp), expander->err);
	if (!vector_merge(&expander->word_exp, &word_exp, expander->word_exp.len))
		expander->err = error_sys();
	word_free(&word_exp);
	return (string_free(&param_exp), string_free(&sep), expander->err);
}

t_error	expand_positional_at(t_expander *expander, t_word_item_opt opt)
{
	size_t				i;
	t_string			param;
	const t_positionals	*params;
	t_word				word_exp;

	expander->err = params_get_positionals(&params);
	if (expander->err.type)
		return (expander->err);
	i = 0;
	while (i < params->len)
	{
		param = ((t_string *)params->data)[i];
		expander->err = from_str(&word_exp, &param, opt);
		if (expander->err.type)
			return (expander->err);
		expander->err = append_param_as_field(expander, word_exp, i);
		if (expander->err.type)
			return (word_free(&word_exp), expander->err);
		i++;
	}
	return (expander->err);
}

t_error	emit_positionals(t_expander *expander, char c, t_word_item_opt opt)
{
	if (c == '*')
		return (expand_positional_star(expander, opt));
	return (expand_positional_at(expander, opt));
}
