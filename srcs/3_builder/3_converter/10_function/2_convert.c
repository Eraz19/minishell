#include "error.h"
#include "parser_type.h"
#include "ast_type.h"
#include "converter_priv.h"
#include <stdlib.h>

/*
function_body    : compound_command
                 | compound_command redirect_list
                 ;
*/
static inline t_error	convert_function_body(
	t_parser *parser,
	t_cst_node *body,
	t_ast_function_def *out)
{
	t_cst_node	*redir;
	t_error		err;

	out->body = malloc(sizeof(*out->body));
	if (!out->body)
		return (error_sys());
	err = convert_compound_command(parser, body->children[0], out->body);
	if (err.type == ERR_NO && body->child_count > 1)
	{
		redir = body->children[1];
		return (convert_redirection_add_list(parser, redir, &out->redirs));
	}
	return (err);
}

/*
function_definition : fname '(' ')' linebreak function_body
                 ;
fname            : NAME
                 ;
*/
t_error	convert_function(
	t_parser *parser,
	t_cst_node *function_definition,
	t_ast_function_def *out)
{
	t_cst_node	*fname;
	t_cst_node	*body;
	t_error		err;

	ast_function_def_init(out);
	fname = function_definition->children[0];
	err = converter_dup_buff(parser, fname, 0, &out->name);
	body = function_definition->children[4];
	if (err.type == ERR_NO)
		err = convert_function_body(parser, body, out);
	if (err.type)
		ast_function_def_free(out);
	return (err);
}
