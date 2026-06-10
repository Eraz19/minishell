/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 16:00:43 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/10 16:54:50 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "scanner.h"

void	scanner_init(t_scanner *state)
{
	*state = (t_scanner){0};
	lexer_init(&state->lexer);
	alias_init(&state->alias);
	heredoc_init(&state->heredoc);
}

void	scanner_free(t_scanner *state)
{
	if (state->arg.command != NULL)
		free(state->arg.command);
	lexer_free(&state->lexer);
	alias_free(&state->alias);
	heredoc_free(&state->heredoc);
	*state = (t_scanner){0};
}

t_error	scanner_load(t_scanner *state, t_scanner_mode mode, const char *arg)
{
	state->mode = mode;
	lexer_load(&state->lexer, mode == SCAN_MODE_STDIN);
	heredoc_load(&state->heredoc, mode == SCAN_MODE_STDIN);
	if (mode == SCAN_MODE_STRING)
		return (state->arg.command = arg, state->err);
	else if (mode == SCAN_MODE_FILE)
		return (state->arg.path = arg, state->err);
	return (state->err);
}
