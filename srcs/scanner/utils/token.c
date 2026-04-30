/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 17:49:34 by adouieb           #+#    #+#             */
/*   Updated: 2026/04/29 18:08:28 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "scanner.h"

void	free_token(void *token_ptr)
{
	t_token	*token;

	if (token_ptr == NULL)
		return ;
	token = (t_token *)token_ptr;
	buff_free(&token->value);
	*token = (t_token){0};
	free(token);
}

bool	is_contains_eof(t_lexer *lexer)
{
	t_token	*token;

	if (lexer == NULL || lexer->tokens == NULL)
		return (false);
	if (list_get_size(lexer->tokens) == 0)
		return (false);
	token = list_get_content_last(lexer->tokens);
	if (token == NULL)
		return (false);
	return (token->type == EOF);
}

