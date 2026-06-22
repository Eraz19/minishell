#include "shell.h"
#include "builder.h"
#include "lr_machine.h"
#include "parser.h"

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
	return (
		parser_build_qualifiers_table(&builder->parser, &builder->lr_machine));
}

t_error	builder_get_ast(t_ast_node **dst_ast)
{
	t_builder	*builder;
	t_error		err;

	builder = shell_get_builder();
	if (!builder)
		return (error(ERR_SHELL_NOT_FOUND));
	err = parser_build_cst(&builder->parser, &builder->lr_machine);
	if (err.type != ERR_NO)
		return (err);
	*dst_ast = NULL;
	// TODO: converter_convert(builder->parser->cst, dst_ast)
	return (error(ERR_NO));
}

t_error	builder_reset(void)
{
	t_builder	*builder;

	builder = shell_get_builder();
	if (!builder)
		return (error(ERR_SHELL_NOT_FOUND));
	return (parser_reset(&builder->parser));
}

void	builder_free(t_builder *builder)
{
	lr_machine_free(&builder->lr_machine);
	parser_free(&builder->parser);
	// TODO: converter_free(&builder->converter);
}
