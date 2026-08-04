/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_recognition_context.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:13:04 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 16:37:49 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h> // DEBUG
#include "token_recognition_context.h"

t_error	token_recognition_consume_context(t_lexer *lexer, t_context context)
{
	if (context == CONTEXT_SQUOTE)
		return (scan_squote_context(lexer));
	if (context == CONTEXT_DQUOTE)
		return (scan_dquote_context(lexer));
	if (context == CONTEXT_DOLLAR_SQUOTE)
		return (scan_dollar_squote_context(lexer));
	if (context == CONTEXT_BACKTICK)
		return (scan_backtick_context(lexer));
	if (context == CONTEXT_ARITH)
		return (scan_arith_context(lexer));
	if (context == CONTEXT_PARAM)
		return (scan_param_context(lexer));
	if (context == CONTEXT_CMD_SUB)
		return (scan_cmd_sub_context(lexer));
	assert(false);
	return (lexer->err);
}
