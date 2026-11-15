/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   great.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:13:14 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/06 22:43:59 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_recognition_priv.h"
#include "token_recognition_operator.h"

bool	is_char_great_fit_operator(t_lexer *lexer)
{
	if (lexer->token->type == TOKEN_LESS)
		return (true);
	else if (lexer->token->type == TOKEN_GREAT)
		return (true);
	else if (!is_inside_operator(lexer))
		return (true);
	return (false);
}

t_error	token_recognition_consume_great(t_lexer *lexer)
{
	if (lexer->token->type == TOKEN_LESS)
		return (token_recognition_consume(lexer, TOKEN_LESSGREAT, 1));
	else if (lexer->token->type == TOKEN_GREAT)
		return (token_recognition_consume(lexer, TOKEN_DGREAT, 1));
	else if (lexer->token->type == TOKEN_NONE)
		return (token_recognition_consume(lexer, TOKEN_GREAT, 1));
	else
		return (lexer->err = error(ERR_POSIX_SYNTAX));
}
