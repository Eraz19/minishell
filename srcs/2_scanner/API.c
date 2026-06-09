/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   API.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 16:05:54 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/08 14:59:48 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "__reader.h"
#include "__scanner.h"

t_error	scanner_next_token(t_token *token)
{
	t_scanner	*state;

	if (token == NULL)
		return (ERR_NULL_ARGS);
	state = shell_get_scanner();
	if ()

	if (state->mode == SCAN_MODE_FILE && state->lexer.input == NULL)
		reader_file_input(&state->lexer.input, state->arg.path);
	else if (state->mode == SCAN_MODE_STRING && state->lexer.input == NULL)
		state->lexer.input = state->arg.command;
	else if (state->lexer.input == NULL)
		reader_new_input(&state->lexer.input);
	if (state->err)
		return (state->err);
	if (lexer_next_token(&state->lexer, token))		
		return (state->err = state->lexer.err, state->err);
	else if (token->type == NEWLINE_)
	{
		if (heredoc_consume(&state->heredoc, &state->lexer))
			return (state->err = state->heredoc.err, state->err);
		heredoc_reset(&state->heredoc);
	}
	return (state->err);
}

t_error	scanner_report_io_here(char **res, t_buff delim, t_heredoc_mode mode)
{
	t_here_queue_item	item;
	t_scanner			*state;

	state = shell_get_scanner();
	if (heredoc_create_tmp_file(&state->heredoc, res))
		return (state->err = state->heredoc.err, state->err);
	item = (t_here_queue_item){.path = *res, .mode = mode, .delim = delim};
	state->err = here_queue_push(&state->heredoc.queue, item);
	return (state->err);
}


