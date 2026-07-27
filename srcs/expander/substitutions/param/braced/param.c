#include "env.h"
#include "param_braced_.h"
#include "param_expansion_.h"

static t_error	braced_param_state(
					t_expander *expander,
					const t_string *name,
					t_string *value,
					bool *is_set)
{
	*is_set = true;
	expander->err = env_get_from_const(name->data, value);
	if (expander->err.type == ERR_VAR_NOT_FOUND)
	{
		*is_set = false;
		if (!string_init(value, 0, "", -1))
			return (expander->err = error_sys());
		return (expander->err = error(ERR_NO));
	}
	if (expander->err.type)
		return (expander->err);
	if (value->data == NULL && !string_init(value, 0, "", -1))
		return (expander->err = error_sys());
	return (expander->err);
}

static t_error	braced_param_simple(
					t_expander *expander,
					t_string *name,
					t_word_item_opt opt)
{
	t_string	value;

	expander->err = braced_expect_close(expander);
	if (expander->err.type)
		return (string_free(name), expander->err);
	expander->err = braced_lookup(expander, name, &value);
	string_free(name);
	if (expander->err.type)
		return (expander->err);
	return (braced_finish(expander, &value, opt));
}

static t_error	braced_operator(
					t_expander *expander,
					t_param_exp *param_exp,
					size_t remaining)
{
	expander->err = parse_braced_op(expander,
						&param_exp->has_colon,
						&param_exp->op_char,
						&param_exp->op_span);
	if (expander->err.type)
		return (string_free(&param_exp->param_name), expander->err);
	expander->err = braced_take_operand(
						expander,
						remaining - param_exp->op_span,
						&param_exp->operand_word);
	if (expander->err.type)
		return (string_free(&param_exp->param_name), expander->err);
	if (braced_expect_close(expander).type
		|| word_remove(&expander->word, 0, 1).type)
		return (string_free(&param_exp->param_name),
			word_free(&param_exp->operand_word), expander->err);
	if (braced_param_state(expander, &param_exp->param_name,
			&param_exp->param_value, &param_exp->param_is_set).type)
		return (string_free(&param_exp->param_name),
			word_free(&param_exp->operand_word), expander->err);
	expander->err = braced_dispatch(expander, param_exp);
	return (string_free(&param_exp->param_name),
		string_free(&param_exp->param_value), expander->err);
}

t_error	expand_braced_param(
			t_expander *expander,
			size_t body_len,
			t_word_item_opt origin)
{
	t_param_exp	param_exp;
	size_t		len_before;
	size_t		operator_len;

	param_exp.result_opt = origin;
	len_before = expander->word.len;
	expander->err = get_param_name(expander, &param_exp.param_name, true);
	if (expander->err.type)
		return (expander->err);
	if (len_before - expander->word.len == body_len)
		return (braced_param_simple(expander,
					&param_exp.param_name,
					param_exp.result_opt));
	operator_len = body_len - (len_before - expander->word.len);
	return (braced_operator(expander, &param_exp, operator_len));
}
