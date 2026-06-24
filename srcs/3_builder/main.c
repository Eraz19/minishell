#include "shell.h"
#include "builder.h"
#include "lr_machine.h"
#include "parser.h"
#include "converter.h"

void	builder_init(t_builder *builder)
{
	lr_machine_init(&builder->lr_machine);
	parser_init(&builder->parser);
	// TODO: converter_init(&builder->converter);
}

t_error	builder_load(t_builder *builder)
{
	t_error	err;

	err = lr_machine_build_tables(&builder->lr_machine);
	if (err.type != ERR_NO)
		return (err);
	// TODO: converter_load(&builder->converter);
	return (parser_build_qualifiers_table(
		&builder->parser,
		&builder->lr_machine));
}

# include "debug.h"	// DEBUG
t_error	builder_get_ast(t_ast_root *dst_ast)
{
	t_builder	*builder;
	t_error		err;

	builder = shell_get_builder();
	if (!builder)
		return (error(ERR_SHELL_NOT_FOUND));
	err = parser_build_cst(&builder->parser, &builder->lr_machine);
	if (err.type != ERR_NO)
		return (err);
	fprintf(stderr, "--------------------------------------------------\n");
	fprintf(stderr, "[BUILDER] CST built:\n");
	debug_dump_cst_node(builder->parser.cst);
	fprintf(stderr, "--------------------------------------------------\n");
	convert_cst_to_ast(builder->parser.cst, dst_ast);
	fprintf(stderr, "[BUILDER] AST built:\n");
	debug_dump_ast(dst_ast);
	fprintf(stderr, "--------------------------------------------------\n");
	return (error(ERR_NO));
}

t_error	builder_reset(void)
{
	t_builder	*builder;

	builder = shell_get_builder();
	if (!builder)
		return (error(ERR_SHELL_NOT_FOUND));
	// TODO: converter_reset(&builder->converter);
	return (parser_reset(&builder->parser));
}

void	builder_free(t_builder *builder)
{
	lr_machine_free(&builder->lr_machine);
	parser_free(&builder->parser);
	// TODO: converter_free(&builder->converter);
}
