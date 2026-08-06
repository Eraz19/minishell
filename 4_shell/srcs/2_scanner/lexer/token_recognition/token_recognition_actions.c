/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_recognition_actions.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:13:57 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 16:34:57 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_recognition_priv.h"

void	token_recognition_delimit(t_lexer *lexer)
{
	lexer->emited_token = true;
	if (lexer->token->value.len == 0)
		lexer->token->index.end = lexer->token->index.start;
}

void	token_recognition_advance(t_lexer *lexer, size_t offset)
{
	lexer->input->i += offset;
}

t_error	token_recognition_consume(
			t_lexer *lexer,
			t_token_type type,
			size_t iter)
{
	size_t	i;
	char	current_char;

	i = 0;
	while (i < iter)
	{
		if (lexer->input_stack.len == 1)
		{
			if (lexer->token->value.len == 0)
				lexer->token->index.start = (ssize_t)lexer->input->i;
			lexer->token->index.end = (ssize_t)lexer->input->i;
			lexer->last_index = lexer->token->index;
		}
		else
			lexer->token->index = lexer->last_index;
		current_char = lexer->input->str.data[lexer->input->i];
		if (!string_append_n(&lexer->token->value, &current_char, 1))
			return (lexer->err = error_sys());
		lexer->token->type = type;
		token_recognition_advance(lexer, 1);
		i++;
	}
	return (lexer->err);
}
