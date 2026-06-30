#include "context.h"

bool	is_context_arith_start(char *str)
{
	if (str[1] != '\0' && str[2] != '\0')
		return (str[0] == '$' && str[1] == '(' && str[2] == '(');
	return (false);
}

bool	is_context_arith_ending(char c, void *nesting_depth)
{
	if (nesting_depth == NULL)
		return (false);
	return (c == ')' && *((size_t *)nesting_depth) == 0);
}
