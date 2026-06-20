/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 16:00:43 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/20 12:01:38 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "scanner_.h"
# include "logs.h"	// DEBUG

t_error	scanner_init(t_scanner *state)
{
	*state = (t_scanner){0};
	state->lexer = malloc(sizeof(t_lexer));
	if (state->lexer == NULL)
		return (error_sys());
	lexer_init(state->lexer);
	heredoc_init(&state->heredoc);
	return (error(ERR_NO));
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
	print_title("scanner_load()");
	state->mode = mode;
	print_pass("mode set to %i\n", (int)mode);
	// TO_CHECK (START)
	state->lexer = malloc(sizeof(*state->lexer));
	if (!state->lexer)
		return (state->err = error_sys(), state->err);
	lexer_init(state->lexer);
	// TO_CHECK (END)
	lexer_load(state->lexer, mode == SCAN_STDIN);
	print_pass("lexer_load()\n");
	heredoc_load(&state->heredoc, mode == SCAN_STDIN);
	print_pass("heredoc_load()\n");
	print_result("scanner_load()");
	if (mode == SCAN_STRING)
		return (state->source = source, state->err);
	else if (mode == SCAN_FILE)
		return (state->source = source, state->err);
	return (state->err);
}
