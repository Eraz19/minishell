#include "builder.h"
#include "lr_machine.h"
#include "parser.h"
#include "converter.h"
# include "debug.h"		// DEBUG
# include <assert.h>	// DEBUG

t_error	builder_load(t_builder *builder)
{
	assert(builder != NULL);
	return (lr_machine_build_tables(&builder->lr_machine));
}

t_error	build_ast(t_parser *parser, const t_lr_machine *machine, t_ast_root *dst_ast)
{
	t_error		err;

	assert(dst_ast != NULL);
	err = parser_build_cst(parser, machine);
	if (err.type)
		return (err);
	debug_dump_cst(parser->cst);
	err = convert_cst_to_ast(parser, parser->cst, dst_ast);
	if (err.type == ERR_NO)
		debug_dump_ast(dst_ast);
	return (err);
}
