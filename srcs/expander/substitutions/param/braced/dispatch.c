#include "param_braced_.h"

static bool	braced_triggered(const t_param_exp *param_exp)
{
	if (param_exp->has_colon)
		return (!param_exp->param_is_set || param_exp->param_value.len == 0);
	return (!param_exp->param_is_set);
}

static t_error	braced_triggered_action(
	t_expander *expander,
	t_param_exp *param_exp)
{
	if (param_exp->op_char == '-')
		return (braced_use_operand(expander, &param_exp->operand_word,
				param_exp->result_opt));
	if (param_exp->op_char == '=')
		return (braced_assign(expander, &param_exp->param_name,
				param_exp->result_opt, &param_exp->operand_word));
	if (param_exp->op_char == '?')
		return (braced_error(expander, &param_exp->param_name,
				&param_exp->operand_word));
	return (word_free(&param_exp->operand_word), expander->err);
}

static t_error	braced_untriggered_action(
	t_expander *expander,
	t_param_exp *param_exp)
{
	if (param_exp->op_char == '+')
		return (braced_use_operand(expander, &param_exp->operand_word,
				param_exp->result_opt));
	return (braced_use_value(expander, &param_exp->param_value,
			param_exp->result_opt, &param_exp->operand_word));
}

t_error	braced_dispatch(t_expander *expander, t_param_exp *param_exp)
{
	if (param_exp->op_char == '#' || param_exp->op_char == '%')
		return (braced_remove(expander, param_exp));
	if (braced_triggered(param_exp))
		return (braced_triggered_action(expander, param_exp));
	return (braced_untriggered_action(expander, param_exp));
}
