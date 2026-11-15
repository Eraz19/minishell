/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inside_word_rule.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:13:45 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 16:34:26 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_recognition_priv.h"
#include "token_recognition_context.h"

bool	is_inside_word(t_lexer *lexer)
{
	return (lexer->token->type == TOKEN_TOKEN);
}

t_error	recognize_token_inside_word(t_lexer *lexer)
{
	char	current_char;

	current_char = lexer->input->str.data[lexer->input->i];
	if (current_char == '\\')
		return (none_context_escape_rules(lexer));
	else
	{
		if (current_char == '=' && lexer->token->assignment_offset == -1)
			lexer->token->assignment_offset = (ssize_t)lexer->token->value.len;
		return (token_recognition_consume(lexer, TOKEN_TOKEN, 1));
	}
}
