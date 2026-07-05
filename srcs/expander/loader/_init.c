#include "word_.h"
#include "loader_.h"

void	loader_init(t_loader *loader)
{
	*loader = (t_loader){0};
	context_stack_init(&loader->stack);
	word_init(&loader->loaded_word);
	context_stack_init(&loader->loading_stack);
}

void	loader_free(t_loader *loader)
{
	context_stack_free(&loader->stack);
	word_free(&loader->loaded_word);
	context_stack_free(&loader->loading_stack);
	if (loader->context_item)
		loader->context_item = NULL;
	*loader = (t_loader){0};
}

t_error	loader_load(t_loader *loader, t_expander_args *args)
{
	if (!string_dup(&loader->word, &args->value))
		return (loader->err = error_sys());
	if (args->contexts == NULL)
		return (loader->err);
	return (loader->err = context_stack_dup(&loader->stack, args->contexts));
}
