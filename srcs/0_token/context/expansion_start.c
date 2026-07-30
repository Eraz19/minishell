#include "context.h"

bool	is_context_param_start(char *str)
{
	return (str[0] == '$' && str[1] == '{');
}

bool	is_context_arith_start(char *str)
{
	return (str[0] == '$' && str[1] == '(' && str[2] == '(');
}

bool	is_context_cmd_sub_start(char *str)
{
	return (str[0] == '$' && str[1] == '(');
}

bool	is_context_backtick_start(char *str)
{
	return (str[0] == '`');
}

bool	is_expansion_context_start(char *str, t_context *context)
{
	if (is_context_param_start(str))
		return (*context = CONTEXT_PARAM, true);
	else if (is_context_arith_start(str))
		return (*context = CONTEXT_ARITH, true);
	else if (is_context_cmd_sub_start(str))
		return (*context = CONTEXT_CMD_SUB, true);
	else if (is_context_backtick_start(str))
		return (*context = CONTEXT_BACKTICK, true);
	return (false);
}
