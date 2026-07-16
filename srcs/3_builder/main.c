#include "shell.h"
#include "builder.h"
#include "lr_machine.h"
#include "parser.h"
#include "converter.h"
# include "debug.h"		// DEBUG
# include <assert.h>	// DEBUG

void	builder_init(t_builder *builder)
{
	assert(builder != NULL);
	lr_machine_init(&builder->lr_machine);
	parser_init(&builder->parser);
}

t_error	builder_load(t_builder *builder)
{
	t_error	err;

	assert(builder != NULL);
	err = lr_machine_build_tables(&builder->lr_machine);
	if (err.type != ERR_NO)
		return (err);
	return (parser_build_qualifiers_table(
		&builder->parser,
		&builder->lr_machine));
}

t_error	build_ast(t_ast_root *dst_ast)
{
	t_builder	*builder;
	t_error		err;

	assert(dst_ast != NULL);
	builder = shell_get_builder();
	if (!builder)
		return (error(ERR_SHELL_NOT_FOUND));
	err = parser_build_cst(&builder->parser, &builder->lr_machine);
	if (err.type)
		return (err);
	debug_dump_cst(builder->parser.cst);
	convert_cst_to_ast(&builder->parser, builder->parser.cst, dst_ast);
	debug_dump_ast(dst_ast);
	return (error(ERR_NO));
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
