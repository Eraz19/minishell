#include "context.h"

bool	is_expansion_context(char *str, t_context *context)
{
	if (is_context_param_start(str))
		return (*context = PARAM, true);
	else if (is_context_arith_start(str))
		return (*context = ARITH, true);
	else if (is_context_cmd_sub_start(str))
		return (*context = CMD_SUB, true);
	else if (is_context_backtick_start(str))
		return (*context = BACKTICK, true);
	return (false);
}

bool	is_in_expansion_whitelist(char c, t_context context)
{
	if (context == NONE_)
		return (is_in_context_none_whitelist(c));
	else if (context == PARAM)
		return (is_in_context_param_whitelist(c));
	else if (context == BACKTICK)
		return (is_in_context_backtick_whitelist(c));
	else
		return (false);
}
