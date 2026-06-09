/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 14:13:58 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/05 20:07:38 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "__lexer_context.h"

t_error	lexer_context(t_lexer *state, t_context context)
{
	if (context == SQUOTE)
		return (context_squote(state));
	if (context == DQUOTE)
		return (context_dquote(state));
	if (context == DOLLAR_SQUOTE)
		return (context_dollar_squote(state));
	if (context == BACKTICK)
		return (context_backtick(state));
	if (context == ARITH)
		return (context_arith(state));
	if (context == PARAM)
		return (context_param(state));
	if (context == CMD_SUB)
		return (state->err = ERR_NOT_IMPLEMENTED, true);
	if (context == NONE_)
		return (state->err = ERR_INCOHERENT_STATE, true);
	return (state->err = ERR_INCOHERENT_STATE, true);
}
