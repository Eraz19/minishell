#include "context.h"

bool	is_context_quoting(t_context context)
{
	return (context == CONTEXT_SQUOTE
		|| context == CONTEXT_DQUOTE
		|| context == CONTEXT_DOLLAR_SQUOTE);
}
