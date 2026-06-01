/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 16:00:43 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/29 17:57:56 by adouieb          ###   ########.fr       */
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
	if (state->origin.command)
		free(state->origin.command);
	lexer_free(&state->lexer);
	reader_free(&state->reader);
	*state = (t_scanner){0};
}

t_error	scanner_load(
	t_scanner *state,
	t_scanner_mode mode,
	t_scanner_origin origin)
{
	state->mode = mode;
	reader_load(&state->reader, state->lexer.ctx);
	lexer_load(&state->lexer, mode == SCAN_MODE_STDIN);
	if (mode == SCAN_MODE_STRING)
		return (state->origin.command = origin.command, ERR_NO);
	else if (mode == SCAN_MODE_FILE)
		return (state->origin.path = origin.path, ERR_NO);
	return (ERR_NO);
}
