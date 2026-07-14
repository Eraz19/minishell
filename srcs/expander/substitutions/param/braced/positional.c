#include "params.h"
#include "param_braced_.h"
#include "param_expansion_.h"

static t_error	braced_positional_bare(
					t_expander *expander,
					t_positional_exp *positional_exp)
{
	expander->err = emit_positionals(
		expander,
		positional_exp->symbol,
		positional_exp->result_opt);
	if (expander->err.type)
		return (expander->err);
	if (braced_expect_close(expander).type)
		return (expander->err);
	return (expander->err = word_remove(&expander->word, 0, 1));
}

static t_error	braced_positional_error(
					t_expander *expander,
					t_positional_exp *positional_exp)
{
	t_string	name;
	char		symbol[2];

	symbol[0] = positional_exp->symbol;
	symbol[1] = '\0';
	if (!string_init(&name, 0, symbol, -1))
	{
		expander->err = error_sys();
		return (word_free(&positional_exp->operand_word), expander->err);
	}
	expander->err = braced_error(
						expander,
						&name,
						&positional_exp->operand_word);
	return (string_free(&name), expander->err);
}

static t_error	braced_positional_apply(
					t_expander *expander,
					t_positional_exp *positional_exp)
{
	if (positional_exp->op_char == '=')
	{
		word_free(&positional_exp->operand_word);
		return (expander->err = error(ERR_VAR_INVALID_NAME));
	}
	if (positional_exp->op_char == '+')
	{
		if (positional_exp->is_triggered)
			return (word_free(&positional_exp->operand_word), expander->err);
		return (braced_use_operand(expander,
					&positional_exp->operand_word,
					positional_exp->result_opt));
	}
	if (!positional_exp->is_triggered)
		return (word_free(
			&positional_exp->operand_word),
			emit_positionals(expander,
				positional_exp->symbol,
				positional_exp->result_opt));
	if (positional_exp->op_char == '-')
		return (braced_use_operand(expander,
					&positional_exp->operand_word,
					positional_exp->result_opt));
	return (braced_positional_error(expander, positional_exp));
}

static t_error	braced_positional_op(
					t_expander *expander,
					t_positional_exp *positional_exp,
					size_t body_len)
{
	bool				colon;
	size_t				op_items;
	const t_positionals	*params;

	expander->err = parse_braced_op(
						expander,
						&colon,
						&positional_exp->op_char,
						&op_items);
	if (expander->err.type)
		return (expander->err);
	expander->err = braced_take_operand(expander,
						body_len - 1 - op_items,
						&positional_exp->operand_word);
	if (expander->err.type)
		return (expander->err);
	if (braced_expect_close(expander).type
		|| word_remove(&expander->word, 0, 1).type)
		return (word_free(&positional_exp->operand_word), expander->err);
	expander->err = params_get_positionals(&params);
	if (expander->err.type)
		return (word_free(&positional_exp->operand_word), expander->err);
	(void)colon;
	positional_exp->is_triggered = (params->len == 0);
	return (braced_positional_apply(expander, positional_exp));
}

t_error	expand_braced_positional(
			t_expander *expander,
			size_t body_len,
			t_word_item_opt origin)
{
	t_positional_exp	positional_exp;
	t_word_item			item;

	expander->err = word_get(&item, &expander->word, 0);
	if (expander->err.type)
		return (expander->err);
	positional_exp.symbol = item.c;
	positional_exp.result_opt = origin;
	positional_exp.result_opt.is_expand_res = true;
	expander->err = word_remove(&expander->word, 0, 1);
	if (expander->err.type)
		return (expander->err);
	if (body_len == 1)
		return (braced_positional_bare(expander, &positional_exp));
	return (braced_positional_op(expander, &positional_exp, body_len));
}
