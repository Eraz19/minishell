/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blank_delimiter_rule.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:13:30 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 16:13:31 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_recognition_priv.h"

t_error	recognize_token_blank_delimiter(t_lexer *lexer)
{
	char	current_char;

	if (lexer->token->type != TOKEN_NONE)
		return (token_recognition_delimit(lexer), lexer->err);
	current_char = lexer->input->str.data[lexer->input->i];
	while (is_blank(current_char) && current_char != '\0')
		current_char = lexer->input->str.data[++lexer->input->i];
	return (lexer->err);
}
