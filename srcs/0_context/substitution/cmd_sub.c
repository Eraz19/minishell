#include "context.h"

bool	is_context_cmd_sub_start(char *str)
{
	return (str[0] == '$' && str[1] == '(');
}
