/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_comment_rule.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:13:33 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 16:13:34 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_recognition_priv.h"

bool	is_comment_start(t_lexer *lexer)
{
	return (lexer->input->str.data[lexer->input->i] == '#');
}

void	recognize_token_escape_comment(t_lexer *lexer)
{
	char	current_char;

	current_char = lexer->input->str.data[lexer->input->i];
	while (!is_context_none_ending(current_char, NULL) && current_char != '\n')
		current_char = lexer->input->str.data[++lexer->input->i];
}
