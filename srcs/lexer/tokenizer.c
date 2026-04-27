/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 11:37:31 by adouieb           #+#    #+#             */
/*   Updated: 2026/04/27 15:08:29 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_lexer.h"

t_raw_string	remove_escapable_newlines(t_raw_string input)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == '\\' && input[i + 1] == '\n')
		{
			i += 2;
			continue ;
		}
		input[j++] = input[i++];
	}
	input[j] = '\0';
	return (input);
}



void	lex_line(t_lexer *lexer, t_raw_string input)
{	
	lexer->index = 0;
	lexer->token_stream = NULL;
	lexer->heredoc_stack = NULL;
	lexer->state.char_escaped = false;
	lexer->state.mode = LEXER_MODE_DEFAULT;
	lexer->state.quote_mode = QUOTE_MODE_NONE;
	lexer->input = remove_escapable_newlines(input);
}
