#include "libft.h"
#include "shell.h"
#include "params.h"
#include "history.h"
#include "expander.h"
#include "reader_.h"

static bool	prompt_excl_append(t_string *res, const t_string *val, size_t *i)
{
	t_history	*history;

	if (val->data[*i] == '!' && val->data[*i + 1] == '!')
		return (*i += 2, string_append_n(res, "!", 1));
	if (val->data[*i] == '!')
	{
		*i += 1;
		history = shell_get_history();
		if (history == NULL)
			return (string_append_n(res, "!", 1));
		return (string_append_format(res, "%u",
				(unsigned int)(history->list.len + 1)));
	}
	*i += 1;
	return (string_append_n(res, &val->data[*i - 1], 1));
}

static t_error	prompt_expand_exclamation(t_string *value)
{
	t_string	res;
	size_t		i;

	(void)string_init(&res, 0, NULL, 0);
	i = 0;
	while (i < value->len)
	{
		if (!prompt_excl_append(&res, value, &i))
			return (string_free(&res), error_sys());
	}
	string_free(value);
	*value = res;
	return (error(ERR_NO));
}

static t_error	prompt_expand_params(t_string *value)
{
	t_error		err;
	t_string	expanded;
	t_expansion	exp;

	err = expand_str(&exp, value, EXP_PARAM);
	if (err.type)
		return (err);
	if (exp.len != 1)
		return (expansion_free(&exp), error(ERR_EXP_RESULT_INCOHERENT));
	err = expansion_take(&exp, 0, &expanded);
	expansion_free(&exp);
	if (err.type)
		return (err);
	string_free(value);
	*value = expanded;
	return (error(ERR_NO));
}

t_error	reader_prompt(const char *name, t_string *dst)
{
	t_error	err;

	err = params_get_from_const(name, dst);
	if (err.type == ERR_VAR_NOT_FOUND)
		return (error(ERR_NO));
	if (err.type)
		return (err);
	if (dst->len == 0)
		return (error(ERR_NO));
	if (str_cmp(name, "PS1") == 0)
		err = prompt_expand_exclamation(dst);
	if (err.type == ERR_NO)
		err = prompt_expand_params(dst);
	if (err.type)
		return (error_print(err, "scanner", name, NULL, NULL),
			error(ERR_NO));
	return (error(ERR_NO));
}
