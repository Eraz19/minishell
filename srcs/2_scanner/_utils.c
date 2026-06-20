/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 10:12:50 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/19 16:33:37 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alias.h"
#include "reader_.h"
#include "scanner_.h"

bool	is_EOF(t_scanner *state)
{
	return (state->lexer->reached_EOI &&
		state->mode != SCAN_STDIN &&
		state->lexer->input_stack.len == 0);
}

t_error	scanner_read_input(t_scanner *state) 
{ 
	t_input_stack_item	*item;

	state->err = input_stack_item_init(&item);
	if (state->err.type)
		return (state->err);
	if (state->mode == SCAN_FILE)
		state->err = reader_file_input(&item->str, state->source);
	else if (state->mode == SCAN_STRING)
	{
		item->str = str_dup(state->source);
		if (item->str == NULL)
			state->err = error_sys();
	}
	else if (state->mode == SCAN_STDIN)
		state->err = reader_new_input(&item->str); 
	if (state->err.type || item->str == NULL)
		return (input_stack_item_free(&item), state->err);
	return (state->err = input_stack_push(&state->lexer->input_stack, item));
}

t_error	scanner_heredoc_store(t_scanner *state)
{
	t_input_stack_item	*item;
	
	if (state->lexer->input != NULL)
	{
		item = state->lexer->input;
		state->err = heredoc_store_all(item->str, &item->i);
		if (state->err.type)
			return (state->err = state->heredoc.err);
	}
	return (state->err);
}

t_error	scanner_alias_expand(t_scanner *state, t_token *token)
{
	t_input_stack_item	*item;

	state->err = input_stack_item_init(&item);
	if (state->err.type)
		return (state->err);
	state->err = alias_expand_token(&item->str, &token->value);
	if (state->err.type || item->str == NULL)
		return (input_stack_item_free(&item), state->err);
	input_stack_push(&state->lexer->input_stack, item);
	token_free(token);
	if (lexer_next_token(state->lexer, token).type)
		return (state->err = state->lexer->err);
	return (state->err);
}
