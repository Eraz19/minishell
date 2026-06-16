/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_sub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 14:22:55 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/16 15:05:36 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_.h"
	
t_error	context_cmd_sub(t_lexer *state)
{
	size_t			start;

	start = state->token->value.len;
	// call function to run in subshell
	state->err = token_context_queue_push(
		&state->token->contexts,
		start,
		state->token->value.len,
		CMD_SUB);
	return (state->err);
}
