/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 12:16:22 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/04 17:48:32 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "scanner.h"

void	lexer_init(t_lexer *lexer)
{
	lexer->index = 0;
	lexer->input = NULL;
	lexer->start = NULL;
	lexer->quotes = NONE_;
	lexer->is_eof = false;
	lexer->tokens = NULL;
}

void	free_lexer(t_lexer **lexer_ptr)
{
	t_lexer	*lexer;

	if (lexer_ptr == NULL || *lexer_ptr == NULL)
		return ;
	lexer = *lexer_ptr;
	if (lexer->input != NULL)
		free(lexer->input);
	if (lexer->tokens != NULL)
		list_rm_all(&lexer->tokens, free_token);
	*lexer = (t_lexer){0};
	free(lexer);
	*lexer_ptr = NULL;
}

bool	add_new_token(t_lexer *lexer, t_token *token)
{
	if (lexer == NULL || token == NULL)
		return (false);
	if (list_add_end(&lexer->tokens, token) == false)
		return (free_token(token), false);
	return (true);
}
