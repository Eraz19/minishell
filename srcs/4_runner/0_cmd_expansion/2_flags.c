#include "cmd_expansion.h"

t_exp_flag	cmd_regular_expansion_flags(void)
{
	return (EXP_TILDE_NORMAL | EXP_PARAM | EXP_DOLLAR_SQUOTE | EXP_CMD_SUB
		| EXP_ARITH | EXP_FIELD_SPLIT | EXP_PATH_NAME | EXP_QUOTE_REMOVAL);
}

t_exp_flag	cmd_assignment_expansion_flags(void)
{
	return (EXP_TILDE_ASSIGNMENT | EXP_PARAM | EXP_DOLLAR_SQUOTE | EXP_CMD_SUB
		| EXP_ARITH | EXP_QUOTE_REMOVAL);
}

t_exp_flag	cmd_case_expansion_flags(void)
{
	return (EXP_TILDE_NORMAL | EXP_PARAM | EXP_DOLLAR_SQUOTE | EXP_CMD_SUB
		| EXP_ARITH | EXP_QUOTE_REMOVAL);
}
