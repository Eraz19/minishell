/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 14:29:44 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/01 11:13:37 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_lexer.h"
#include "./context/_context.h"

bool	lexer_context(t_lexer *state, t_scanner_ctx ctx)
{
	if (ctx == SQUOTE)
		return (ctx_handle(state, ctx_squote_rules()));
	if (ctx == DQUOTE)
		return (ctx_handle(state, ctx_dquote_rules()));
	if (ctx == DOLLAR_SQUOTE)
		return (ctx_handle(state, ctx_dollar_squote_rules()));
	if (ctx == BACKTICK)
		return (ctx_handle(state, ctx_backtick_rules()));
	if (ctx == ARITH)
		return (ctx_arith(state));
	if (ctx == PARAM)
		return (ctx_handle(state, ctx_param_rules()));
	if (ctx == CMD_SUB)
		return (state->err = ERR_NOT_IMPLEMENTED, true);
	if (ctx == NONE_)
		return (state->err = ERR_INCOHERENT_STATE, true);
	return (state->err = ERR_INCOHERENT_STATE, true);
}
