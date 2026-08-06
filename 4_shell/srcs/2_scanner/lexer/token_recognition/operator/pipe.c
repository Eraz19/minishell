/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:13:20 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/06 22:44:05 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_recognition_priv.h"
#include "token_recognition_operator.h"

bool	is_char_pipe_fit_operator(t_lexer *lexer)
{
	if (lexer->token->type == TOKEN_PIPE)
		return (true);
	else if (lexer->token->type == TOKEN_GREAT)
		return (true);
	else if (!is_inside_operator(lexer))
		return (true);
	return (false);
}

t_error	token_recognition_consume_pipe(t_lexer *lexer)
{
	if (lexer->token->type == TOKEN_PIPE)
		return (token_recognition_consume(lexer, TOKEN_OR_IF, 1));
	else if (lexer->token->type == TOKEN_GREAT)
		return (token_recognition_consume(lexer, TOKEN_CLOBBER, 1));
	else if (lexer->token->type == TOKEN_NONE)
		return (token_recognition_consume(lexer, TOKEN_PIPE, 1));
	else
		return (lexer->err = error(ERR_POSIX_SYNTAX));
}
