#include "param_braced_.h"
#include "expander_substitutions_.h"

t_error	parse_braced_op(
	t_expander *expander,
	bool *colon,
	char *op,
	size_t *op_items)
{
	t_word_item	first;
	t_word_item	second;

	expander->err = word_get(&first, &expander->word, 0);
	if (expander->err.type)
		return (expander->err);
	*colon = (first.c == ':');
	if (*colon)
	{
		expander->err = word_get(&second, &expander->word, 1);
		if (expander->err.type)
			return (expander->err);
		*op = second.c;
		*op_items = 2;
	}
	else
	{
		*op = first.c;
		*op_items = 1;
	}
	if (*op != '-' && *op != '=' && *op != '?' && *op != '+')
		return (expander->err = error(ERR_NOT_IMPLEMENTED));
	return (expander->err = word_remove(&expander->word, 0, *op_items));
}

t_error	braced_take_operand(
	t_expander *expander,
	size_t operand_len,
	t_word *operand)
{
	size_t		i;
	t_word_item	item;

	word_init(operand);
	i = 0;
	while (i < operand_len)
	{
		expander->err = word_get(&item, &expander->word, i);
		if (expander->err.type)
			return (word_free(operand), expander->err);
		expander->err = word_push(operand, item);
		if (expander->err.type)
			return (word_free(operand), expander->err);
		i++;
	}
	return (expander->err = word_remove(&expander->word, 0, operand_len));
}

t_error	expand_operand(t_expander *expander, t_word *operand, t_word *out)
{
	t_word	saved_word;
	t_word	saved_word_exp;

	saved_word = expander->word;
	saved_word_exp = expander->word_exp;
	expander->word = *operand;
	word_init(&expander->word_exp);
	while (expander->word.len > 0)
	{
		if (substitution_char(expander).type)
			break ;
	}
	word_free(&expander->word);
	*out = expander->word_exp;
	expander->word = saved_word;
	expander->word_exp = saved_word_exp;
	return (expander->err);
}

t_error	braced_operand_str(t_expander *expander, t_word *operand,
		t_string *out)
{
	t_word	expanded;

	expander->err = expand_operand(expander, operand, &expanded);
	if (expander->err.type)
		return (word_free(&expanded), expander->err);
	expander->err = to_str(out, &expanded, 0, expanded.len);
	return (word_free(&expanded), expander->err);
}

t_error	braced_use_operand(
	t_expander *expander,
	t_word *operand,
	t_word_item_opt opt)
{
	t_string	operand_str;

	expander->err = braced_operand_str(expander, operand, &operand_str);
	if (expander->err.type)
		return (expander->err);
	expander->err = braced_push_value(expander, &operand_str, opt);
	return (string_free(&operand_str), expander->err);
}
