/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   API.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 16:05:54 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/19 15:51:30 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "alias.h"
#include "reader_.h"
#include "scanner_.h"

t_error	scanner_next_token(t_token *token)
{
	t_scanner	*state;

	state = shell_get_scanner();
	if (state == NULL)
		return (ERR_SHELL_NOT_FOUND);
	if (state->lexer->reached_EOI)
	{
		state->err = alias_on_expansion_end();
		if (state->err)
			return (state->err);
	}
	if (is_EOF(state))
		return (token->type = EOF_, state->err);
	if (state->lexer->input_stack.len == 0 && scanner_read_input(state))
		return (state->err);
	if (lexer_next_token(state->lexer, token))
		return (state->err = state->lexer->err, state->err);
	else if (token->type == NEWLINE_ && state->heredoc.queue.len > 0)
		return (scanner_heredoc_store(state));
	else if (token->type == TOKEN)
		return (scanner_alias_expand(state, token));
	return (state->err);
}

t_error	scanner_report_io_here(char **path, char *delim, t_heredoc_mode mode)
{
	t_scanner	*state;

	state = shell_get_scanner();
	if (state == NULL)
		return (ERR_SHELL_NOT_FOUND);
	if (heredoc_add_to_queue(path, delim, mode))
		return (state->err = state->heredoc.err, state->err);
	return (state->err);
}
