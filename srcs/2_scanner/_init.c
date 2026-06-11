/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 16:00:43 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/10 18:45:10 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "scanner.h"

void	scanner_init(t_scanner *state)
{
	*state = (t_scanner){0};
	lexer_init(&state->lexer);
	heredoc_init(&state->heredoc);
}

void	scanner_free(t_scanner *state)
{
	lexer_free(&state->lexer);
	heredoc_free(&state->heredoc);
	*state = (t_scanner){0};
}

t_error	scanner_load(t_scanner *state, t_scanner_mode mode, const char *source)
{
	state->mode = mode;
	lexer_load(&state->lexer, mode == SCAN_MODE_STDIN);
	heredoc_load(&state->heredoc, mode == SCAN_MODE_STDIN);
	if (mode == SCAN_MODE_STRING)
		return (state->source = source, state->err);
	else if (mode == SCAN_MODE_FILE)
		return (state->source = source, state->err);
	return (state->err);
}
