/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 19:48:06 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/09 16:53:43 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "__reader.h"
#include "__lexer_context.h"

static t_error	context_EOI(t_lexer *state)
{
	if (state->is_tty)
		state->err = reader_continuation(&state->input);
	else
		state->err = ERR_UNEXPECTED_EOI;
	return (state->err);
}

t_error	lexer_context_unescape(t_lexer *state, t_unescape_args args)
{
	if (state->input[state->i] == '\0')
		return (context_EOI(state));
	else if (args.special_handler != NULL)
		return (args.special_handler(state, args.special_args));
	else
		return (lexer_consume(state, state->token.type, 1));
}

static t_error	context_escape_next_char(t_lexer *state, t_escape_args args)
{
	bool	in_special_context;

	in_special_context = false;
	if (args.is_in_special_context != NULL)
		in_special_context = args.is_in_special_context(state);
	if (in_special_context && args.is_in_special_whitelist != NULL)
	{
		if (args.is_in_special_whitelist(state->input[state->i]))
			lexer_consume(state, state->token.type, 1);
	}
	else if (!in_special_context && args.is_in_whitelist != NULL)
	{
		if (args.is_in_whitelist(state->input[state->i]))
			lexer_consume(state, state->token.type, 1);
	}
	else
		state->err = ERR_INCOHERENT_STATE;
	return (state->err);
}

t_error	lexer_context_escape(t_lexer *state, t_escape_args args)
{
	if (args.enable_line_continuation && state->input[state->i + 1] == '\n')
	{
		lexer_advance(state, 2);
		if (state->input[state->i] == '\0')
			return (context_EOI(state));
	}
	else if (state->input[state->i] == '\0')
		return (context_EOI(state));
	else
	{
		if (lexer_consume(state, state->token.type, 1))
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

	state->token.type = TOKEN;
	state->err = context_stack_push(&state->context, args.context);
	if (state->err)
		return (state->err);
	lexer_consume(state, state->token.type, args.opening_len);
	while (true)
	{
		if (state->err)
			return (state->err);
		str = state->input + state->i;
		if (args.is_end != NULL && args.is_end(*str, args.unescaped_args))
			break ;
		else if (*str == '\\')
			args.escape(state);
		else if (args.quoting != NULL && args.is_quoting(str, &context))
			args.quoting(state, context);
		else if (args.expansion != NULL && args.is_expansion(str, &context))
			args.expansion(state, context);
		else
			args.unescaped(state, args.unescaped_args);
	}
	return (state->err = context_stack_pop(&state->context), state->err);
}
