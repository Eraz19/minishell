#include <stdlib.h>
#include "context.h"

bool	is_context_param_ending(char c, void *_)
{
	return (c == '}');
}

bool	is_context_backtick_ending(char c, void *_)
{
	return (c == '`');
}

bool	is_context_arith_ending(char c, void *nesting_depth)
{
	if (nesting_depth == NULL)
		return (false);
	return (c == ')' && *((size_t *)nesting_depth) == 0);
}
