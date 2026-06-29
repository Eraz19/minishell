#include "shell.h"
#include "builder.h"
#include "parser.h"
# include <assert.h>	// DEBUG

t_error	builder_can_next_word_be_a_cmd_name(bool *dst)
{
	t_builder	*builder;

	assert(dst != NULL);
	builder = shell_get_builder();
	if (!builder)
		return (error(ERR_SHELL_NOT_FOUND));
	return (parser_can_next_token_be_a_cmd_name_or_word(
		&builder->parser,
		&builder->lr_machine,
		dst));
}
