/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   less.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:13:16 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 16:13:17 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h> // DEBUG
#include "token_recognition_priv.h"
#include "token_recognition_operator.h"

bool	is_char_less_fit_operator(t_lexer *lexer)
{
	if (lexer->token->type == TOKEN_LESS)
		return (true);
	else if (!is_inside_operator(lexer))
		return (true);
	return (false);
}

t_error	token_recognition_consume_less(t_lexer *lexer)
{
	if (lexer->token->type == TOKEN_LESS)
		return (token_recognition_consume(lexer, TOKEN_DLESS, 1));
	else if (lexer->token->type == TOKEN_NONE)
		return (token_recognition_consume(lexer, TOKEN_LESS, 1));
	else
		return (lexer->err = error(ERR_POSIX_SYNTAX));
}
