/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_recognition_operator.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:13:25 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 16:53:50 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h> // DEBUG
#include "token_recognition_priv.h"
#include "token_recognition_operator.h"

bool	is_new_operator(t_lexer *lexer)
{
	return (!is_inside_operator(lexer) && is_operator_char(lexer));
}

bool	is_operator_char(t_lexer *lexer)
{
	char	current_char;

	current_char = lexer->input->str.data[lexer->input->i];
	if (current_char == '\n' && !is_inside_operator(lexer))
		return (true);
	else if (current_char == '(' && !is_inside_operator(lexer))
		return (true);
	else if (current_char == ')' && !is_inside_operator(lexer))
		return (true);
	else if (current_char == ';')
		return (is_char_semicolon_fit_operator(lexer));
	else if (current_char == '&')
		return (is_char_ampersand_fit_operator(lexer));
	else if (current_char == '|')
		return (is_char_pipe_fit_operator(lexer));
	else if (current_char == '<')
		return (is_char_less_fit_operator(lexer));
	else if (current_char == '>')
		return (is_char_great_fit_operator(lexer));
	else if (current_char == '-' && lexer->token->type == TOKEN_DLESS)
		return (true);
	return (false);
}

bool	is_inside_operator(t_lexer *lexer)
{
	t_token_type	type;

	type = lexer->token->type;
	return (type != TOKEN_NONE && type != TOKEN_TOKEN);
}

t_error	token_recognition_consume_operator(t_lexer *lexer)
{
	char	current_char;

	current_char = lexer->input->str.data[lexer->input->i];
	if (current_char == '\n')
		return (token_recognition_consume(lexer, TOKEN_NEWLINE, 1));
	else if (current_char == '(')
		return (token_recognition_consume(lexer, TOKEN_LPARENTHESIS, 1));
	else if (current_char == ')')
		return (token_recognition_consume(lexer, TOKEN_RPARENTHESIS, 1));
	else if (current_char == ';')
		return (token_recognition_consume_semicolon(lexer));
	else if (current_char == '&')
		return (token_recognition_consume_ampersand(lexer));
	else if (current_char == '|')
		return (token_recognition_consume_pipe(lexer));
	else if (current_char == '<')
		return (token_recognition_consume_less(lexer));
	else if (current_char == '>')
		return (token_recognition_consume_great(lexer));
	else if (current_char == '-')
		return (token_recognition_consume(lexer, TOKEN_DLESSDASH, 1));
	else
		return (lexer->err = error(ERR_POSIX_SYNTAX));
}
