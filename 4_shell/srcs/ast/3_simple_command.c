/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_simple_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:35:21 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:35:22 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include <assert.h>	// DEBUG

void	ast_simple_command_init(t_ast_scmd *simple_command)
{
	assert(simple_command != NULL);
	token_pool_init(&simple_command->assignments);
	token_pool_init(&simple_command->words);
	ast_redir_list_init(&simple_command->redirs);
}

t_error	ast_simple_command_dup(void *dst, const void *src)
{
	t_ast_scmd			*dst_scmd;
	const t_ast_scmd	*src_scmd;
	t_error				err;

	dst_scmd = (t_ast_scmd *)dst;
	src_scmd = (const t_ast_scmd *)src;
	ast_simple_command_init(dst_scmd);
	err = token_pool_deep_dup(&dst_scmd->assignments, &src_scmd->assignments);
	if (err.type == ERR_NO)
		err = token_pool_deep_dup(&dst_scmd->words, &src_scmd->words);
	if (err.type == ERR_NO)
		err = ast_redir_list_dup(&dst_scmd->redirs, &src_scmd->redirs);
	if (err.type)
		return (ast_simple_command_free(dst_scmd), err);
	return (error(ERR_NO));
}

void	ast_simple_command_free(void *simple_command)
{
	t_ast_scmd	*cmd;

	assert(simple_command != NULL);
	cmd = (t_ast_scmd *)simple_command;
	token_pool_free(&cmd->assignments);
	token_pool_free(&cmd->words);
	ast_redir_list_free(&cmd->redirs);
}
