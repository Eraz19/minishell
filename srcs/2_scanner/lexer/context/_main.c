/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 14:13:58 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/09 16:51:30 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "__lexer_context.h"

t_error	lexer_context(t_lexer *state, t_context context)
{
	if (context == SQUOTE)
		return (lexer_context_squote(state));
	if (context == DQUOTE)
		return (lexer_context_dquote(state));
	if (context == DOLLAR_SQUOTE)
		return (lexer_context_dollar_squote(state));
	if (context == BACKTICK)
		return (lexer_context_backtick(state));
	if (context == ARITH)
		return (lexer_context_arith(state));
	if (context == PARAM)
		return (lexer_context_param(state));
	if (context == CMD_SUB)
		return (state->err = ERR_NOT_IMPLEMENTED, true);
	if (context == NONE_)
		return (state->err = ERR_INCOHERENT_STATE, true);
	return (state->err = ERR_INCOHERENT_STATE, true);
}
