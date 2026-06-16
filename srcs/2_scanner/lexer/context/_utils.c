/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 19:48:06 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/16 10:44:35 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader_.h"
#include "lexer_context_.h"

static t_error	context_end(t_lexer *state, t_context_args args)
{
	lexer_consume(state, state->token->type, args.closing_len);
	return (state->err = context_stack_pop(&state->input->context));
}

t_error	lexer_context_unescape(t_lexer *state, t_unescape_args args)
{
	if (state->input->str[state->input->i] == '\0')
		return (context_EOI(state));
	else if (args.special_handler != NULL)
		return (args.special_handler(state, args.special_args));
	else
		return (lexer_consume(state, state->token->type, 1));
}

t_error	lexer_context_escape(t_lexer *state, t_escape_args args)
{
	if (args.enable_line_continuation &&
		state->input->str[state->input->i + 1] == '\n')
	{
		lexer_advance(state, 2);
		if (state->input->str[state->input->i] == '\0')
			return (context_EOI(state));
	}
	else if (state->input->str[state->input->i] == '\0')
		return (context_EOI(state));
	else
	{
		if (lexer_consume(state, state->token->type, 1))
			return (state->err);	
		if (context_escape_next_char(state, args))
			return (state->err);
	}
	return (state->err);
}

t_error	lexer_context_scan(t_lexer *state, t_context_args args)
{
	char		*str;
	t_context	context;

	state->token->type = TOKEN;
	state->err = context_stack_push(&state->input->context, args.context);
	if (state->err)
		return (state->err);
	lexer_consume(state, state->token->type, args.opening_len);
	while (true)
	{
		if (state->err)
			return (state->err);
		str = state->input->str + state->input->i;
		if (args.is_end != NULL && args.is_end(*str, args.unescaped_args))
			return (context_end(state, args));
		else if (*str == '\\')
			args.escape(state);
		else if (args.quoting != NULL && args.is_quoting(str, &context))
			args.quoting(state, context);
		else if (args.expansion != NULL && args.is_expansion(str, &context))
			args.expansion(state, context);
		else
			args.unescaped(state, args.unescaped_args);
	}
}
