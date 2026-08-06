/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_context_rule.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:13:36 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 16:13:37 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_recognition_context.h"

t_error	recognize_token_expansion_context(t_lexer *lexer, t_context context)
{
	if (context != CONTEXT_ARITH)
		return (token_recognition_consume_context(lexer, context));
	else
	{
		token_recognition_consume_context(lexer, CONTEXT_ARITH);
		if (lexer->err.type == ERR_CTX_END_NOT_FOUND)
		{
			lexer->err.type = ERR_NO;
			return (token_recognition_consume_context(lexer, CONTEXT_CMD_SUB));
		}
		return (lexer->err);
	}
}
