#include "context.h"

bool	is_substitution_context(char *str, t_context *context)
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

bool	is_in_substitution_whitelist(char c, t_context context)
{
	if (context == CONTEXT_NONE)
		return (is_in_context_none_whitelist(c));
	else if (context == CONTEXT_PARAM)
		return (is_in_context_param_whitelist(c));
	else if (context == CONTEXT_BACKTICK)
		return (is_in_context_backtick_whitelist(c));
	else
		return (false);
}
