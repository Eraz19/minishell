/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 10:28:04 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/29 17:55:56 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_lexer.h"
#include "token/_token.h"

void	lexer_init(t_lexer *state)
{
	if (state == NULL)
		return ;
	*state = (t_lexer){0};
	token_init(&state->token);
	ctx_stack_init(state->ctx);
	here_queue_init(state->queue);
}

void	lexer_free(t_lexer *state)
{
	if (state == NULL)
		return ;
	token_free(&state->token);
	ctx_stack_free(state->ctx);
	here_queue_free(state->queue);
	*state = (t_lexer){0};
}

void	lexer_load(t_lexer *state, bool is_tty)
{
	if (state == NULL)
		return ;
	state->is_tty = is_tty;
}

t_error	lexer_reset(t_lexer *state)
{
	bool	is_tty;

	if (state == NULL)
		return (ERR_NULL_ARGS);
	is_tty = state->is_tty;
	lexer_free(state);
	lexer_init(state);
	state->is_tty = is_tty;
	return (ERR_NO);
}
