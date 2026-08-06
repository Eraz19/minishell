/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:07:50 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 17:17:15 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "convert_command_priv.h"
#include "converter_priv.h"
#include "error.h"
#include "parser_type.h"
#include "ast.h"
#include <assert.h>	// DEBUG

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
