/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 16:00:43 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/15 23:58:07 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "scanner_.h"

t_error	scanner_init(t_scanner *state)
{
	*state = (t_scanner){0};
	state->lexer = malloc(sizeof(t_lexer));
	if (state->lexer == NULL)
		return (ERR_LIBC);
	lexer_init(state->lexer);
	heredoc_init(&state->heredoc);
	return (ERR_NO);
}

void	scanner_free(t_scanner *state)
{
	if (state->lexer != NULL)
	{
		lexer_free(state->lexer);
		free(state->lexer);
	}
	heredoc_free(&state->heredoc);
	*state = (t_scanner){0};
}

t_error	scanner_load(t_scanner *state, t_scanner_mode mode, const char *source)
{
	state->mode = mode;
	lexer_load(state->lexer, mode == SCAN_STDIN);
	heredoc_load(&state->heredoc, mode == SCAN_STDIN);
	if (mode == SCAN_STRING)
		return (state->source = source, state->err);
	else if (mode == SCAN_FILE)
		return (state->source = source, state->err);
	return (state->err);
}
