/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:11:09 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 16:11:10 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ast.h"
#include "token.h"

void	token_init(t_token *token)
{
	*token = (t_token){0};
	token->index.end = -1;
	token->index.start = -1;
	token->index.error = -1;
	token->assignment_offset = -1;
	ast_vector_init(&token->ast_vector);
	context_stack_init(&token->contexts);
	(void)string_init(&token->value, 0, NULL, 0);
}

void	token_free(t_token *token)
{
	string_free(&token->value);
	ast_vector_free(&token->ast_vector);
	context_stack_free(&token->contexts);
	token->index.end = -1;
	token->index.start = -1;
	token->index.error = -1;
	token->type = TOKEN_NONE;
	token->assignment_offset = -1;
}

void	token_free_void(void *token)
{
	token_free(token);
}

void	token_free_owned(void *token)
{
	token_free(token);
	free(token);
}
