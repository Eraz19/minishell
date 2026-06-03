/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtick.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 14:19:48 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/01 11:15:53 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_context.h"
#include "../token/_token.h"

static bool	is_backtick_squote_surrounded(t_lexer *state)
{
	t_scanner_ctx	*ctx;
	t_scanner_ctx	surrounding_ctx;

    if (state->ctx.len < 2)
        return (false);
    ctx = (t_scanner_ctx *)state->ctx.data;
	surrounding_ctx = ctx[state->ctx.len - 2];
    return (surrounding_ctx == DQUOTE || surrounding_ctx == ARITH);
}

static bool	ctx_backtick_escape(t_lexer *state)
{
	t_escape_handler	args;

	args.is_in_whitelist = is_in_ctx_backtick_whitelist;
	args.is_in_special_context = is_backtick_squote_surrounded;
	args.is_in_special_whitelist = is_in_ctx_backtick_special_whitelist;
	args.enable_line_continuation = is_backtick_squote_surrounded(state);
	return (ctx_escape(state, args));
}

static bool	ctx_backtick_unescape(t_lexer *state, void *_)
{
	t_unescape_handler	args;

	args.special_args = NULL;
	args.special_handler = NULL;
	return (ctx_unescape(state, args));
}

t_ctx_handler	ctx_backtick_rules(void)
{
	t_ctx_handler	res;

	res.opening_len = 1;
	res.ctx_mode = BACKTICK;
	res.unescaped_args = NULL;
	res.quoting = lexer_quoting;
	res.escape = ctx_backtick_escape;
	res.is_end = is_ctx_backtick_ending;
	res.substitution = lexer_substitution;
	res.unescaped = ctx_backtick_unescape;
	return (res);
}
