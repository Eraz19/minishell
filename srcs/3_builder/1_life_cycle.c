#include "builder.h"
#include "lr_machine.h"
#include "parser.h"
# include <assert.h>	// DEBUG

void	builder_init(t_builder *builder)
{
	assert(builder != NULL);
	lr_machine_init(&builder->lr_machine);
	parser_init(&builder->parser);
}

void	builder_clear(t_builder *builder)
{
	parser_clear(&builder->parser);
}

void	builder_free(t_builder *builder)
{
	assert(builder != NULL);
	lr_machine_free(&builder->lr_machine);
	parser_free(&builder->parser);
}

void	builder_cmd_sub_init(
			const t_builder *main_builder,
			t_cmd_sub_builder *cmd_sub_builder)
{
	cmd_sub_builder->lr_machine = &main_builder->lr_machine;
	parser_cmd_sub_init(&main_builder->parser, &cmd_sub_builder->parser);
}

void	builder_cmd_sub_free(t_cmd_sub_builder *cmd_sub_builder)
{
	cmd_sub_builder->lr_machine = NULL;
	parser_cmd_sub_free(&cmd_sub_builder->parser);
}
