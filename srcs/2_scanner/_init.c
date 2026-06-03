/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 16:00:43 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/03 15:07:51 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "_scanner.h"

void	scanner_init(t_scanner *state)
{
	if (state == NULL)
		return ;
	*state = (t_scanner){0};
	lexer_init(&state->lexer);
	reader_init(&state->reader);
}

void	scanner_free(t_scanner *state)
{
	if (state == NULL)
		return ;
	if (state->arg.command)
		free(state->arg.command);
	lexer_free(&state->lexer);
	reader_free(&state->reader);
	*state = (t_scanner){0};
}

t_error	scanner_load(t_scanner *state, t_scanner_mode mode, t_scanner_arg arg)
{
	if (state == NULL)
		return (ERR_NULL_ARGS);
	state->mode = mode;
	reader_load(&state->reader, &state->lexer.ctx);
	lexer_load(&state->lexer, mode == SCAN_MODE_STDIN);
	if (mode == SCAN_MODE_STRING)
		return (state->arg.command = arg.command, state->err);
	else if (mode == SCAN_MODE_FILE)
		return (state->arg.path = arg.path, state->err);
	return (state->err);
}
