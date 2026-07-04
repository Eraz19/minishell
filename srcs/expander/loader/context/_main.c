#include <stdlib.h>
#include "loader_context_.h"

bool	is_substitution_start(t_loader *loader)
{
	t_context_stack_item	*item;

	if (!is_context_start(loader, &item))
		return (false);
	return (!is_quoting_type(item->context));
}

bool	is_quoting_start(t_loader *loader)
{
	t_context_stack_item	*item;

	if (!is_context_start(loader, &item))
		return (false);
	return (is_quoting_type(item->context));
}

t_error	loader_push_context(t_loader *loader)
{
	t_context_stack_item	*item;

	if (loader->stack.len == 0)
		return (loader->err);
	loader->err = context_stack_fpop(&loader->stack, &item);
	if (loader->err.type)
		return (loader->err);
	loader->err = context_stack_push(&loader->loading_stack, item);
	if (loader->err.type)
		return (free(item), loader->err);
	return (loader->context_item = item, loader->err);
}

t_error	loader_pop_context(t_loader *loader)
{
	t_context_stack_item	*item;
	size_t					last_i;
	
	loader->err = context_stack_bpop(&loader->loading_stack, &item);
	if (loader->err.type)
		return (loader->err);
	free(item);
	if (loader->loading_stack.len > 0)
	{
		last_i = loader->loading_stack.len - 1;
		loader->err = context_stack_get(&loader->loading_stack, &item, last_i);
		if (loader->err.type)
			return (loader->err);
		loader->context_item = item;
	}
	else
		loader->context_item = NULL;
	return (loader->err);
}

