#include "context.h"

bool	is_context_param_start(char *str)
{
	if (str[1] != '\0')
		return (str[0] == '$' && str[1] == '{');
	return (false);
}

bool	is_in_context_param_whitelist(char c)
{
	return ((void)c, true);
}

bool	is_context_param_ending(char c, void *_)
{
	return (c == '}');
}

