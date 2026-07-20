#include "builder.h"
#include "lr_machine.h"
#include "parser.h"
# include <assert.h>	// DEBUG

void	builder_init(t_builder *builder, t_scanner *scanner)
{
	assert(builder != NULL);
	lr_machine_init(&builder->lr_machine);
	parser_init(&builder->parser, scanner);
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
