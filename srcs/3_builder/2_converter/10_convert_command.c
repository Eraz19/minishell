#include "error.h"
#include "parser_type.h"
#include "ast.h"
#include "converter_priv.h"
# include <assert.h>	// DEBUG

/*
brace_group      : Lbrace compound_list Rbrace
                 ;
*/
static inline t_error	convert_to_list(
							t_parser *parser,
							const t_cst_node *node,
							t_ast_command *out)
{
	out->type = AST_CMD_LIST;
	if (node->symbol == SYM_brace_group)
		return (convert_list(parser, node->children[1], &out->data.list));
	else if (node->symbol == SYM_subshell)
		return (convert_list(parser, node, &out->data.list));
	return (error(ERR_INCOHERENT_STATE));
}

/*
compound_command : brace_group
                 | subshell
                 | for_clause
                 | case_clause
                 | if_clause
                 | while_clause
                 | until_clause
                 ;
*/
static inline t_error	convert_compound_command_priv(
							t_parser *parser,
							const t_cst_node *compound_command,
							t_ast_command *out)
{
	t_cst_node	*child;

	child = compound_command->children[0];
	if (child->symbol == SYM_brace_group || child->symbol == SYM_subshell)
		return (convert_to_list(parser, child, out));
	else if (child->symbol == SYM_for_clause)
	{
		out->type = AST_CMD_FOR;
		return (convert_for(parser, child, &out->data.for_clause));
	}
	else if (child->symbol == SYM_case_clause)
	{
		out->type = AST_CMD_CASE;
		return (convert_case(parser, child, &out->data.case_clause));
	}
	else if (child->symbol == SYM_if_clause)
	{
		out->type = AST_CMD_IF;
		return (convert_if(parser, child, &out->data.if_clause));
	}
	else
	{
		out->type = AST_CMD_LOOP;
		return (convert_loop(parser, child, &out->data.loop));
	}
}

static inline t_error	convert_to_simple(
							t_parser *parser,
							const t_cst_node *simple,
							t_ast_command *out)
{
	out->type = AST_CMD_SIMPLE;
	return (convert_simple_command(parser, simple, &out->data.simple));
}

static inline t_error	convert_to_function(
							t_parser *parser,
							const t_cst_node *func,
							t_ast_command *out)
{
	out->type = AST_CMD_FUNCTION_DEF;
	return (convert_function(parser, func, &out->data.function_def));
}

t_error	convert_compound_command(
			t_parser *parser,
			const t_cst_node *compound_command,
			t_ast_command *out)
{
	t_error		err;

	assert(parser != NULL);
	assert(compound_command != NULL);
	assert(out != NULL);
	ast_command_init(out);
	err = error(ERR_NO);
	err = convert_compound_command_priv(parser, compound_command, out);
	if (err.type)
		ast_command_free(out);
	return (err);
}

/*
command          : simple_command
                 | compound_command
                 | compound_command redirect_list
                 | function_definition
                 ;
*/
t_error	convert_command(
			t_parser *parser,
			const t_cst_node *command,
			t_ast_command *out)
{
	size_t		i;
	t_cst_node	*child;
	t_error		err;

	assert(parser != NULL);
	assert(command != NULL);
	assert(out != NULL);
	ast_command_init(out);
	err = error(ERR_NO);
	i = 0;
	while (i < command->child_count && err.type == ERR_NO)
	{
		child = command->children[i];
		if (child->symbol == SYM_simple_command)
			err = convert_to_simple(parser, child, out);
		else if (child->symbol == SYM_compound_command)
			err = convert_compound_command_priv(parser, child, out);
		else if (child->symbol == SYM_redirect_list)
			err = convert_redirection_add_list(parser, child, &out->redirs);
		else
			err = convert_to_function(parser, child, out);
		i++;
	}
	if (err.type)
		ast_command_free(out);
	return (err);
}
