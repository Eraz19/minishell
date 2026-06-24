#include "error.h"
#include "parser_type.h"
#include "ast_type.h"
#include "converter_priv.h"

static inline t_error	add_pipeline(
	t_parser *parser,
	t_cst_node *node,
	t_ast_and_or *out)
{
	t_ast_pipeline	pipeline;
	t_error			err;

	err = convert_pipeline(parser, node, &pipeline);
	if (err.type)
		return (err);
	if (!vector_push(&out->pipelines, &pipeline))
		return (ast_pipeline_free(&pipeline), error_sys());
	return (error(ERR_NO));
}

static inline t_error	add_operator(bool operator, t_ast_and_or *out)
{
	if (!vector_push(&out->next_on_success, &operator))
		return (error_sys());
	return (error(ERR_NO));
}

static inline t_error	parse_rec(
	t_parser *parser,
	t_cst_node *and_or,
	t_ast_and_or *out)
{
	size_t		i;
	t_cst_node	*child;
	t_error		err;

	err = error(ERR_NO);
	i = 0;
	while (i < and_or->child_count && err.type == ERR_NO)
	{
		child = and_or->children[i];
		if (child->symbol == SYM_and_or)
			err = parse_rec(parser, child, out);
		else if (child->symbol == SYM_pipeline)
			err = add_pipeline(parser, child, out);
		else if (child->symbol == SYM_AND_IF)
			err = add_operator(true, out);
		else if (child->symbol == SYM_OR_IF)
			err = add_operator(false, out);
		i++;
	}
	return (err);
}

/*
and_or           :                         pipeline
                 | and_or AND_IF linebreak pipeline
                 | and_or OR_IF  linebreak pipeline
                 ;
*/
t_error	convert_and_or(
	t_parser *parser,
	t_cst_node *and_or,
	t_ast_and_or *out)
{
	t_error		err;

	ast_and_or_init(out);
	err = parse_rec(parser, and_or, out);
	if (err.type)
		ast_and_or_free(out);
	return (err);
}
