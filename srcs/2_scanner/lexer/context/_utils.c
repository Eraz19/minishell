/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 14:13:58 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/03 15:26:32 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_context.h"
#include "_scanner.h"

bool	ctx_start(t_lexer *state, t_scanner_ctx ctx, size_t len)
{
	if (state->token.type == NONE)
		state->token.type = TOKEN;
	state->err = ctx_stack_push(&state->ctx, ctx);
	if (state->err)
		return (true);
	return (lexer_consume(state, state->token.type, len));
}

bool	ctx_unescape(t_lexer *state, t_unescape_handler args)
{
	if (state->input[state->i] == '\0')
	{
		if (state->is_tty)
			state->err = reader_continuation(&state->input);
		else
			state->err = ERR_UNEXPECTED_EOI;
		return (true);
	}
	else if (args.special_handler != NULL)
		return (args.special_handler(state, args.special_args));
	else
		return (lexer_consume(state, state->token.type, 1));
}

void	ctx_escape_next_char(t_lexer *state, t_escape_handler args)
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
}

bool	ctx_escape(t_lexer *state, t_escape_handler args)
{
	if (args.enable_line_continuation && state->input[state->i + 1] == '\n')
	{
		lexer_advance(state, 2);
		if (state->input[state->i] == '\0')
		{
			if (state->is_tty)
				state->err = reader_continuation(&state->input);
			else
				state->err = ERR_UNEXPECTED_EOI;
		}
	}
	else if (state->input[state->i] == '\0')
	{
		if (state->is_tty)
			state->err = reader_continuation(&state->input);
		else
			state->err = ERR_UNEXPECTED_EOI;
	}
	else
	{
		lexer_consume(state, state->token.type, 1);
		if (state->err == ERR_NO)
			ctx_escape_next_char(state, args);
	}
	return (true);
}

bool	ctx_handle(t_lexer *state, t_ctx_handler args)
{
	ctx_start(state, args.ctx_mode, args.opening_len);
	if (state->err)
		return (true);
	while (true)
	{
		if (state->err)
			return (true);
		else if (args.is_end != NULL && args.is_end(state->input[state->i]))
		{
			lexer_consume(state, state->token.type, 1);
			if (state->err)
				return (true);
			return (state->err = ctx_stack_pop(&state->ctx), true);
		}
		else if (state->input[state->i] == '\\' && args.escape(state))
			continue ;
		else if (args.quoting != NULL && args.quoting(state))
			continue ;
		else if (args.substitution != NULL && args.substitution(state))
			continue ;
		else if (!args.unescaped(state, args.unescaped_args))
			return (true);
	}
}
