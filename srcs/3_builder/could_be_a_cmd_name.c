#include "shell.h"
#include "builder.h"
#include "parser.h"

t_error	builder_can_next_word_be_a_cmd_name(bool *dst)
{
	t_builder	*builder;

	builder = shell_get_builder();
	if (!builder)
		return (error(ERR_SHELL_NOT_FOUND));
	*dst = parser_can_next_token_be_a_cmd_name_or_word(&builder->parser);
	return (error(ERR_NO));
}
