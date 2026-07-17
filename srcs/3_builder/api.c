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

t_error	build_ast(t_builder *builder, t_ast_root *dst_ast)
{
	t_error		err;

	assert(dst_ast != NULL);
	err = parser_build_cst(&builder->parser, &builder->lr_machine);
	if (err.type)
		return (err);
	debug_dump_cst(builder->parser.cst);
	err = convert_cst_to_ast(&builder->parser, builder->parser.cst, dst_ast);
	if (err.type == ERR_NO)
		debug_dump_ast(dst_ast);
	return (err);
}

t_error	build_cmd_sub_ast(
			t_cmd_sub_builder *builder,
			ssize_t *out_closing_index,
			t_ast_root *dst_ast)
{
	t_error	err;

	err = parser_build_cst(&builder->parser, builder->lr_machine);
	if (err.type)
		return (err);
	debug_dump_cst(builder->parser.cst);
	err = convert_cmd_sub_cst_to_ast(&builder->parser, builder->parser.cst,
			dst_ast);
	if (err.type)
		return (err);
	debug_dump_ast(dst_ast);
	*out_closing_index = builder->parser.cmd_sub_end_index;
	return (err);
}
