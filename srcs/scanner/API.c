/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   API.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 11:37:31 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/07 16:39:22 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_scanner.h"

static t_token	*get_next_token_tty(t_lexer *lexer)
{
	t_token	*res;

	res = NULL;
	if (lexer->input == NULL)
		lexer->input = read_tty();
	while (res != NULL)
	{
		if (!lex_line(&res, &lexer->ctx, &lexer->input, &lexer->i))
			return (NULL);
		complete_tty(&lexer->input);
	}
	return (res);
}

static t_token	*get_next_token_non_tty(t_lexer *lexer)
{
	t_token	*res;

	res = NULL;
	if (lexer->input == NULL)
		lexer->input = read_script(lexer->script_path);
	if (!lex_line(&res, &lexer->ctx, &lexer->input, &lexer->i))
		return (NULL);
	return (res);
}

t_token	*get_next_token(t_lexer *lexer)
{
	if (lexer->script_path == NULL)
		return (get_next_token_tty(lexer));
	else
		return (get_next_token_non_tty(lexer));
}
