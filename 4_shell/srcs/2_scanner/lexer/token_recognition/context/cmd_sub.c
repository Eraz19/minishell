/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_sub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:12:46 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/06 22:43:42 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cmd_sub.h"
#include "token_recognition_priv.h"

t_error	scan_cmd_sub_context(t_lexer *lexer)
{
	t_context_stack_item	*item;
	t_ast_vector			*token_ast;
	size_t					cmd_sub_len;
	ssize_t					closing_index;

	lexer->token->type = TOKEN_TOKEN;
	lexer->err = context_stack_item_init(&item, CONTEXT_CMD_SUB);
	if (lexer->err.type)
		return (lexer->err);
	item->start = lexer->token->value.len;
	lexer->err = context_stack_push(&lexer->token->contexts, item);
	if (lexer->err.type)
		return (free(item), lexer->err);
	token_ast = &lexer->token->ast_vector;
	lexer->err = cmd_sub_find_end(&closing_index, token_ast);
	if (lexer->err.type)
		return (lexer->err);
	cmd_sub_len = (size_t)closing_index - lexer->input->i + 1;
	item->end = lexer->token->value.len + cmd_sub_len - 1;
	return (token_recognition_consume(lexer, lexer->token->type, cmd_sub_len));
}
