#include "param_braced_.h"
#include "expander_substitutions_.h"

static t_error	collect_operand_field(t_expander *expander)
{
	if (expander->err.type)
		return (word_free(&expander->word_exp), expander->err);
	expander->err = fields_push(&expander->fields_exp, expander->word_exp);
	if (expander->err.type)
		word_free(&expander->word_exp);
	return (expander->err);
}

static t_error	operand_to_fields(
					t_expander *expander,
					t_word *operand,
					t_fields *out)
{
	t_word		saved_word;
	t_word		saved_word_exp;
	t_fields	saved_fields_exp;
	bool		saved_in_operand;

	saved_word = expander->word;
	saved_word_exp = expander->word_exp;
	saved_fields_exp = expander->fields_exp;
	saved_in_operand = expander->in_operand;
	expander->word = *operand;
	expander->in_operand = false;
	word_init(&expander->word_exp);
	fields_init(&expander->fields_exp);
	while (expander->word.len > 0 && !expander->err.type)
		substitution_char(expander);
	word_free(&expander->word);
	collect_operand_field(expander);
	*out = expander->fields_exp;
	expander->word = saved_word;
	expander->word_exp = saved_word_exp;
	expander->fields_exp = saved_fields_exp;
	expander->in_operand = saved_in_operand;
	return (expander->err);
}

static t_error	emit_field_break(t_expander *expander)
{
	expander->err = fields_push(&expander->fields_exp, expander->word_exp);
	if (expander->err.type)
		return (expander->err);
	return (word_init(&expander->word_exp), expander->err);
}

static t_error	emit_operand_fields(
					t_expander *expander,
					t_fields *fields,
					t_word_item_opt opt)
{
	size_t		i;
	t_word		field;
	t_string	str;

	i = 0;
	while (i < fields->len)
	{
		field = ((t_word *)fields->data)[i];
		expander->err = to_str(&str, &field, 0, field.len);
		if (expander->err.type)
			return (expander->err);
		if (i != 0 && emit_field_break(expander).type)
			return (string_free(&str), expander->err);
		expander->err = braced_push_value(expander, &str, opt);
		string_free(&str);
		if (expander->err.type)
			return (expander->err);
		i++;
	}
	return (expander->err);
}

t_error	braced_use_operand(
			t_expander *expander,
			t_word *operand,
			t_word_item_opt opt)
{
	t_fields	fields;

	expander->err = operand_to_fields(expander, operand, &fields);
	if (expander->err.type)
		return (fields_free(&fields), expander->err);
	expander->err = emit_operand_fields(expander, &fields, opt);
	return (fields_free(&fields), expander->err);
}
