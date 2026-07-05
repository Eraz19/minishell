#include "loader_context_.h"

bool	is_quoting_type(t_context context)
{
	return (context == CONTEXT_SQUOTE
		|| context == CONTEXT_DQUOTE
		|| context == CONTEXT_DOLLAR_SQUOTE
		|| context == CONTEXT_HEREDOC);
}

bool	is_context_start(t_loader *loader, t_context_stack_item **item)
{
	if (loader->stack.len == 0)
		return (false);
	loader->err = context_stack_get(&loader->stack, item, 0);
	if (loader->err.type || *item == NULL)
		return (false);
	return (loader->i == (*item)->start);
}
