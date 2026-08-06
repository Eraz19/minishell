/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_command_priv.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 17:16:07 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 22:46:37 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "converter_priv.h"
#include "convert_command_priv.h"

/*
brace_group      : Lbrace compound_list Rbrace
                 ;
subshell         : '(' compound_list ')'
                 ;
*/
t_error	convert_to_list(
			t_parser *parser,
			const t_cst_node *node,
			t_ast_command *out)
{
	out->type = AST_CMD_LIST;
	if (node->symbol == SYM_brace_group)
		return (convert_list(parser, node->children[1], &out->data.list));
	return (convert_list(parser, node, &out->data.list));
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
t_error	convert_compound_command_priv(
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

t_error	convert_to_simple(
			t_parser *parser,
			const t_cst_node *simple,
			t_ast_command *out)
{
	out->type = AST_CMD_SIMPLE;
	return (convert_simple_command(parser, simple, &out->data.simple));
}

t_error	convert_to_function(
			t_parser *parser,
			const t_cst_node *func,
			t_ast_command *out)
{
	out->type = AST_CMD_FUNCTION_DEF;
	return (convert_function(parser, func, &out->data.function_def));
}
