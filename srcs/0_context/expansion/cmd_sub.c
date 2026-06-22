#include "context.h"

bool	is_context_cmd_sub_start(char *str)
{
	if (str[1] != '\0')
		return (str[0] == '$' && str[1] == '(');
	return (false);
}
