#include "utils.h"
#include "param_braced_.h"

bool	is_valid_braced_op(char op)
{
	return (op == '-' || op == '=' || op == '?' || op == '+'
		|| op == '#' || op == '%');
}

bool	braced_op_is_doubled(const t_word *word, char op)
{
	t_word_item	second;

	if (op != '#' && op != '%')
		return (false);
	if (word_get(&second, word, 1).type)
		return (false);
	return (second.c == op);
}

static t_error	remove_prefix(
	const t_string *value,
	const char *pattern,
	bool largest,
	t_string *out)
{
	size_t	k;
	size_t	cut;

	cut = 0;
	k = 0;
	while (k <= value->len)
	{
		if (match_pattern(pattern, value->data, k))
		{
			cut = k;
			if (!largest)
				break ;
		}
		k++;
	}
	if (!string_init(out, 0, value->data + cut, (long)(value->len - cut)))
		return (error_sys());
	return (error(ERR_NO));
}

static t_error	remove_suffix(
	const t_string *value,
	const char *pattern,
	bool largest,
	t_string *out)
{
	size_t	k;
	size_t	cut;

	cut = 0;
	k = 0;
	while (k <= value->len)
	{
		if (match_pattern(pattern, value->data + value->len - k, k))
		{
			cut = k;
			if (!largest)
				break ;
		}
		k++;
	}
	if (!string_init(out, 0, value->data, (long)(value->len - cut)))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	braced_remove(t_expander *expander, t_param_exp *param_exp)
{
	t_string	pattern;
	t_string	result;

	expander->err = braced_build_pattern(expander,
			&param_exp->operand_word, &pattern);
	if (expander->err.type)
		return (expander->err);
	if (param_exp->op_char == '#')
		expander->err = remove_prefix(&param_exp->param_value, pattern.data,
				param_exp->op_span == 2, &result);
	else
		expander->err = remove_suffix(&param_exp->param_value, pattern.data,
				param_exp->op_span == 2, &result);
	string_free(&pattern);
	if (expander->err.type)
		return (expander->err);
	expander->err = braced_push_value(expander, &result, param_exp->result_opt);
	return (string_free(&result), expander->err);
}
