#include "error.h"
#include "parser_type.h"
#include "ast.h"
#include "converter_priv.h"
#include <assert.h>	// DEBUG

static inline t_error	add_command(
							t_parser *parser,
							const t_cst_node *node,
							t_ast_pipeline *out)
{
	t_ast_command	command;
	t_error			err;

	err = convert_command(parser, node, &command);
	if (err.type)
		return (err);
	if (!vector_push(&out->commands, &command))
		return (err = error_sys(), ast_command_free(&command), err);
	return (error(ERR_NO));
}

static inline t_error	parse_rec(
							t_parser *parser,
							const t_cst_node *node,
							t_ast_pipeline *out)
{
	const t_cst_node	*child;
	size_t				i;
	t_error				err;

	err = error(ERR_NO);
	i = 0;
	while (i < node->child_count && err.type == ERR_NO)
	{
		child = node->children[i];
		if (child->symbol == SYM_pipe_sequence)
			err = parse_rec(parser, child, out);
		else if (child->symbol == SYM_command)
			err = add_command(parser, child, out);
		else if (child->symbol == SYM_Bang)
			out->negated = true;
		i++;
	}
	return (err);
}

/*
pipeline         :      pipe_sequence
                 | Bang pipe_sequence
                 ;
pipe_sequence    :                             command
                 | pipe_sequence '|' linebreak command
                 ;
*/
t_error	convert_pipeline(
			t_parser *parser,
			const t_cst_node *pipeline,
			t_ast_pipeline *out)
{
	t_error		err;

	assert(parser != NULL);
	assert(pipeline != NULL);
	assert(out != NULL);
	ast_pipeline_init(out);
	err = parse_rec(parser, pipeline, out);
	if (err.type)
		ast_pipeline_free(out);
	return (err);
}
