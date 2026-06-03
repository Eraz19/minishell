/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arith.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 14:20:43 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/01 11:14:54 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_context.h"
#include "../token/_token.h"

static bool	ctx_arith_special_handler(t_lexer *state, void *nesting_depth)
{
	if (state->input[state->i] == '(')
	{
		lexer_consume(state, state->token.type, 1);
		if (state->err)
			return (true);
		return ((*((size_t *)nesting_depth))++, true);
	}
	else if (state->input[state->i] == ')')
	{
		lexer_consume(state, state->token.type, 1);
		if (state->err)
			return (true);
		if (*((size_t *)nesting_depth) == 0)
			return (false);
		else
			return ((*((size_t *)nesting_depth))--, true);
	}
	else
		return (lexer_consume(state, state->token.type, 1), true);
}

static bool	ctx_arith_escape(t_lexer *state)
{
	t_escape_handler	args;

	args.is_in_special_context = NULL;
	args.is_in_special_whitelist = NULL;
	args.enable_line_continuation = true;
	args.is_in_whitelist = is_in_ctx_dquote_whitelist;
	return (ctx_escape(state, args));
}

static bool	ctx_arith_unescape(t_lexer *state, void *nesting_depth)
{
	t_unescape_handler	args;
	
	args.special_args = nesting_depth;
	args.special_handler = ctx_arith_special_handler;
	return (ctx_unescape(state, args));
}

t_ctx_handler	ctx_arith_rules(size_t *nesting_depth)
{
	t_ctx_handler	res;

	res.is_end = NULL;
	res.quoting = NULL;
	res.opening_len = 3;
	res.ctx_mode = ARITH;
	res.escape = ctx_arith_escape;
	res.unescaped = ctx_arith_unescape;
	res.unescaped_args = nesting_depth;
	res.substitution = lexer_substitution;
	return (res);
}

bool	ctx_arith(t_lexer *state)
{
	t_lexer_backup	backup;
	size_t			nesting_depth;

	nesting_depth = 0;
	backup = lexer_backup(state);
	ctx_handle(state, ctx_arith_rules(&nesting_depth));
	if (state->err)
		return (true);
	if (state->input[state->i] != ')')
		return (lexer_restore(state, backup), false);
	lexer_consume(state, state->token.type, 1);
	if (state->err)
		return (true);
	return (state->err = ctx_stack_pop(&state->ctx), true);
}
