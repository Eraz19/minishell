#include "shell.h"
#include "builder.h"
#include "lr_machine.h"
#include "parser.h"
#include "converter.h"
# include "debug.h"		// DEBUG
# include <assert.h>	// DEBUG

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

t_error	builder_find_cmd_sub_end(t_cmd_sub_builder *builder, size_t *end_index)
{
	t_error	err;

	err = parser_build_cst(&builder->parser, builder->lr_machine);
	*end_index = builder->parser.cmd_sub_end_index;
	if (err.type == ERR_CMD_SUB_CLOSING_FOUND)
		err.type = ERR_NO;
	return (err);
}
