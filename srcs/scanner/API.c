/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   API.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 11:37:31 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/09 16:30:01 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_scanner.h"

static t_token	*get_next_token_tty(t_lexer *lexer)
{
	t_token	*res;

	//ft_printf("GET_NEXT_TOKEN_TTY\n");
	res = NULL;
	if (lexer->input == NULL)
		lexer->input = read_tty();
	while (res == NULL)
	{
		//ft_printf("ENTER IN LOOP\n");
		if (!lex_line(&res, lexer))
			return (/*ft_printf("LEAVE ERROR GET_NEXT_TOKEN_TTY\n"),*/ NULL);
		if (res == NULL)
			complete_tty(&lexer->input);
	}
	//ft_printf("LEAVE GET_NEXT_TOKEN_TTY\n");
	return (res);
}

static t_token	*get_next_token_non_tty(t_lexer *lexer)
{
	t_token	*res;

	//ft_printf("GET_NEXT_TOKEN_NON_TTY\n");
	res = NULL;
	if (lexer->input == NULL)
		lexer->input = read_script(lexer->script_path);
	if (!lex_line(&res, lexer))
		return (/*ft_printf("LEAVE ERROR GET_NEXT_TOKEN_NON_TTY\n"),*/ NULL);
	//ft_printf("LEAVE GET_NEXT_TOKEN_NON_TTY\n");
	return (res);
}

t_token	*get_next_token(t_lexer *lexer)
{
	t_token *res;

	//ft_printf("GET_NEXT_TOKEN\n");
	if (lexer->script_path == NULL)
	{
		res = get_next_token_tty(lexer);
		return (/*ft_printf("LEAVE GET_NEXT_TOKEN\n"),*/ res);
	}
	else
	{
		res = get_next_token_non_tty(lexer);	
		return (/*ft_printf("LEAVE GET_NEXT_TOKEN\n"),*/ res);
	}
}


