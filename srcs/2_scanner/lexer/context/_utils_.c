/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils_.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 10:41:22 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/17 12:11:34 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader_.h"
#include "lexer_context_.h"

t_error	context_EOI(t_lexer *state)
{
	if (state->is_stdin)
		state->err = reader_continuation(&state->input->str);
	else
		state->err = ERR_UNEXPECTED_EOI;
	return (state->err);
}

t_error	context_escape_next_char(t_lexer *state, t_escape_args args)
{
	bool	in_special_context;

	in_special_context = false;
	if (args.is_in_special_context != NULL)
		in_special_context = args.is_in_special_context(state);
	if (in_special_context && args.is_in_special_whitelist != NULL)
	{
		if (args.is_in_special_whitelist(state->input->str[state->input->i]))
			lexer_consume(state, state->token->type, 1);
	}
	else if (!in_special_context && args.is_in_whitelist != NULL)
	{
		if (args.is_in_whitelist(state->input->str[state->input->i]))
			lexer_consume(state, state->token->type, 1);
	}
	else
		state->err = ERR_INCOHERENT_STATE;
	return (state->err);
}
