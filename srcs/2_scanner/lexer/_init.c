/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 10:28:04 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/05 19:38:04 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "__lexer.h"

void	lexer_init(t_lexer *state)
{
	*state = (t_lexer){0};
	token_init(&state->token);
	context_stack_init(&state->context);
}

void	lexer_free(t_lexer *state)
{
	token_free(&state->token);
	context_stack_free(&state->context);
	*state = (t_lexer){0};
}

void	lexer_load(t_lexer *state, bool is_tty)
{
	state->is_tty = is_tty;
}

void	lexer_reset(t_lexer *state)
{
	bool	is_tty;

	is_tty = state->is_tty;
	lexer_free(state);
	lexer_init(state);
	state->is_tty = is_tty;
}
