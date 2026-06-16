/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 15:37:26 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/10 16:53:15 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_rules_.h"

t_error	lexer_rule_quoting(t_lexer *state, t_context context)
{
	return (lexer_context(state, context));
}

t_error	lexer_rule_expansion(t_lexer *state, t_context context)
{
	if (context != ARITH)
		return (lexer_context(state, context));
	else
	{
		if (lexer_context(state, ARITH) == ERR_CTX_END_NOT_FOUND)
			return (state->err = ERR_NO, lexer_context(state, CMD_SUB));
		return (state->err);
	}
}
