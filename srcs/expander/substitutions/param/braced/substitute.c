#include "params.h"
#include "param_braced_.h"

t_error	braced_use_value(
			t_expander *expander,
			const t_string *value,
			t_word_item_opt opt,
			t_word *operand)
{
	word_free(operand);
	return (braced_push_value(expander, value, opt));
}

t_error	braced_error(
			t_expander *expander,
			const t_string *name,
			t_word *operand)
{
	t_string	msg;

	if (operand->len == 0)
	{
		word_free(operand);
		return (expander->err = error_print(error(ERR_PARAM_NULL_OR_UNSET),
					name->data, NULL, NULL));
	}
	expander->err = braced_operand_str(expander, operand, &msg);
	if (expander->err.type)
		return (expander->err);
	expander->err = error_print(error(ERR_PARAM_NULL_OR_UNSET),
			name->data, msg.data, NULL, NULL);
	return (string_free(&msg), expander->err);
}

static bool	is_assignable_name(const t_string *name)
{
	size_t	i;

	if (name->len == 0 || !(ft_isalpha(name->data[0]) || name->data[0] == '_'))
		return (false);
	i = 1;
	while (i < name->len)
	{
		if (!(ft_isalnum(name->data[i]) || name->data[i] == '_'))
			return (false);
		i++;
	}
	return (true);
}

t_error	braced_assign(
			t_expander *expander,
			const t_string *name,
			t_word_item_opt opt,
			t_word *operand)
{
	t_string	operand_str;

	if (!is_assignable_name(name))
	{
		word_free(operand);
		return (expander->err = error(ERR_VAR_INVALID_NAME));
	}
	expander->err = braced_operand_str(expander, operand, &operand_str);
	if (expander->err.type)
		return (expander->err);
	expander->err = params_set_variable(name, &operand_str, false, false);
	if (expander->err.type == ERR_VAR_READ_ONLY)
		expander->err = error_print(expander->err, name->data, NULL, NULL);
	if (expander->err.type)
		return (string_free(&operand_str), expander->err);
	expander->err = braced_push_value(expander, &operand_str, opt);
	return (string_free(&operand_str), expander->err);
}
