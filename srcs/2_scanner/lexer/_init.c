/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 10:28:04 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/16 00:04:46 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_.h"

void	lexer_init(t_lexer *state)
{
	*state = (t_lexer){0};
	input_stack_init(&state->input_stack);
}

void	lexer_free(t_lexer *state)
{
	input_stack_free(&state->input_stack);
	*state = (t_lexer){0};
}

void	lexer_load(t_lexer *state, bool is_stdin)
{
	state->is_stdin = is_stdin;
}
