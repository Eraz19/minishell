/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   API.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 16:05:54 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/11 17:40:20 by adouieb          ###   ########.fr       */
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
	if (state->lexer.reached_EOI)
	{
		state->err = alias_on_expansion_end();
		if (state->err)
			return (state->err);
	}
	if (is_EOF(state))
		return (token->type = EOF, state->err);
	if (scanner_read_input(state))
		return (state->err);
	if (lexer_next_token(&state->lexer, token))		
		return (state->err = state->lexer.err, state->err);		
	else if (token->type == NEWLINE_ && state->heredoc.queue.len > 0)
		return (scanner_heredoc_store(state));
	else if (token->type == TOKEN)
		return (scanner_alias_expand(state, token));
	return (state->err);
}

t_error	scanner_report_io_here(char **res, t_buff delim, t_heredoc_mode mode)
{
	t_here_queue_item	item;
	t_scanner			*state;

	state = shell_get_scanner();
	if (state == NULL)
		return (ERR_SHELL_NOT_FOUND);
	if (heredoc_create_tmp_file(&state->heredoc, res))
		return (state->err = state->heredoc.err, state->err);
	item = (t_here_queue_item){.path = *res, .mode = mode, .delim = delim};
	state->err = here_queue_push(&state->heredoc.queue, item);
	return (state->err);
}
