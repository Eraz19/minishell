/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_cmd_sub_find_end.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:06:59 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 21:29:11 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_sub.h"
#include "parser.h"
#include "shell.h"

t_error	cmd_sub_find_end(
			ssize_t *out_closing_token_id,
			t_ast_vector *ast_vector)
{
	t_ast_root	ast_root;
	t_parser	*parser;
	t_error		err;

	err = shell_get_new_parser(&parser, SCAN_MODE_CMD_SUB, NULL);
	if (err.type)
		return (err);
	parser->search_cmd_sub_end = true;
	err = parser_get_ast(parser, &ast_root);
	if (err.type == ERR_NO)
	{
		*out_closing_token_id = parser->cmd_sub_end_index;
		err = ast_vector_push(ast_vector, &ast_root);
		if (err.type)
			ast_root_free(&ast_root);
	}
	shell_destroy_last_instance();
	return (err);
}
