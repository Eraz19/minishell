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

	i = 0;
	string_init(&res, 0, NULL, 0);
	while (i < value->len)
	{
		if (!prompt_excl_append(&res, value, &i))
			return (string_free(&res), error_sys());
	}
	string_free(value);
	*value = res;
	return (error(ERR_NO));
}

static t_error	prompt_use_unexpanded(
					const char *name,
					t_string *dst,
					t_string *value,
					t_error err)
{
	(void)error_print(err, "scanner", name, NULL, NULL);
	string_free(dst);
	*dst = *value;
	return (error(ERR_NO));
}

t_error	reader_prompt(const char *name, t_string *dst)
{
	t_error		err;
	t_string	value;
	int			exit_status;

	string_init(dst, 0, NULL, 0);
	err = params_get_from_const(name, &value);
	if (err.type == ERR_VAR_NOT_FOUND)
		return (error(ERR_NO));
	if (err.type)
		return (err);
	if (value.len == 0)
		return (string_free(&value), error(ERR_NO));
	if (str_cmp(name, "PS1") == 0)
		err = prompt_expand_exclamation(&value);
	if (err.type == ERR_NO)
		err = expand_str(dst, &value, &exit_status, EXP_PARAM);
	if (err.type)
		return (prompt_use_unexpanded(name, dst, &value, err));
	return (string_free(&value), error(ERR_NO));
}
