/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_function_def.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:35:37 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 22:49:09 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include <stdlib.h>

void	ast_function_def_init(t_ast_function_def *function_def)
{
	token_init(&function_def->name);
	function_def->body = NULL;
	ast_redir_list_init(&function_def->redirs);
}

t_error	ast_function_def_dup(void *dst, const void *src)
{
	t_ast_function_def			*dst_function_def;
	const t_ast_function_def	*src_function_def;
	t_error						err;

	dst_function_def = (t_ast_function_def *)dst;
	src_function_def = (const t_ast_function_def *)src;
	ast_function_def_init(dst_function_def);
	err = token_dup(&dst_function_def->name, &src_function_def->name);
	if (err.type)
		return (err);
	dst_function_def->body = malloc(sizeof(*dst_function_def->body));
	if (dst_function_def->body == NULL)
		err = error_sys();
	if (err.type == ERR_NO)
		err = ast_command_dup(dst_function_def->body, src_function_def->body);
	if (err.type == ERR_NO)
		err = ast_redir_list_dup(&dst_function_def->redirs,
				&src_function_def->redirs);
	if (err.type)
		return (ast_function_def_free(dst_function_def), err);
	return (error(ERR_NO));
}

void	ast_function_def_free(t_ast_function_def *function_def)
{
	token_free(&function_def->name);
	if (function_def->body)
	{
		ast_command_free(function_def->body);
		free(function_def->body);
		function_def->body = NULL;
	}
	ast_redir_list_free(&function_def->redirs);
}
