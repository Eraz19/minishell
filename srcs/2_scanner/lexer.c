/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 16:09:23 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/01 16:29:43 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./lexer/_lexer.h"

t_error	lexer_next_token(t_token *res, t_lexer *state)
{
	if (state == NULL || res == NULL || state->input == NULL)
		return (ERR_NULL_ARGS);
	state->reached_EOI = false;
	state->emited_token = false;
	lexer_token_recognition(res, state);
	if (state->err)
		return (state->err);
	if (res->type == NEWLINE_ && state->queue.len > 0)
		lexer_heredoc_queue_consume(state);
	return (state->err);
}
