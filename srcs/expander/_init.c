#include "expander_.h"
#include "loader_.h"

void	expander_init(t_expander *expander)
{
	*expander = (t_expander){0};
	expander->assignment_offset = -1;
	fields_init(&expander->fields);
}

void	expander_free(t_expander *expander)
{
	fields_free(&expander->fields);
	fields_free(&expander->fields_exp);
	word_free(&expander->word);
	word_free(&expander->word_exp);
	*expander = (t_expander){0};
}

t_error	expander_load(t_expander *expander, t_expander_args *args)
{
	t_loader	loader;
	t_word		word_copy;

	expander->ifs = args->ifs;
	expander->flags = args->flags;
	expander->exit_status = args->exit_status;
	expander->assignment_offset = args->assignment_offset;
	loader_init(&loader);
	expander->err = loader_load(&loader, args);
	if (expander->err.type)
		return (loader_free(&loader), expander->err);
	while (loader.i < loader.word.len)
	{
		expander->err = loader_prepare_word(&loader);
		if (expander->err.type)
			return (loader_free(&loader), expander->err);
	}
	expander->err = word_dup(&word_copy, &loader.loaded_word);
	if (expander->err.type)
		return (loader_free(&loader), word_free(&word_copy), expander->err);
	expander->err = fields_push(&expander->fields, word_copy);
	if (expander->err.type)
		return (loader_free(&loader), word_free(&word_copy), expander->err);
	return (loader_free(&loader), expander->err);
}
