/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtick.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 14:19:48 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/10 16:50:56 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_rules_.h"
#include "lexer_context_.h"

static bool	is_backtick_squote_surrounded(t_lexer *state)
{
	t_context	*ctx;
	t_context	surrounding_ctx;

    if (state->context.len < 2)
        return (false);
    ctx = (t_context *)state->context.data;
	surrounding_ctx = ctx[state->context.len - 2];
    return (surrounding_ctx == DQUOTE || surrounding_ctx == ARITH);
}

static t_error	context_backtick_escape(t_lexer *state)
{
	t_escape_args	args;

	args.is_in_whitelist = is_in_context_backtick_whitelist;
	args.is_in_special_context = is_backtick_squote_surrounded;
	args.enable_line_continuation = is_backtick_squote_surrounded(state);
	args.is_in_special_whitelist = is_in_context_backtick_special_whitelist;
	return (lexer_context_escape(state, args));
}

static t_error	context_backtick_unescape(t_lexer *state, void *_)
{
	t_unescape_args	args;

	args.special_args = NULL;
	args.special_handler = NULL;
	return (lexer_context_unescape(state, args));
}

static t_context_args	context_backtick_rules(void)
{
	t_context_args	res;

	res.opening_len = 1;
	res.context = BACKTICK;
	res.unescaped_args = NULL;
	res.quoting = lexer_rule_quoting;
	res.is_quoting = is_quoting_context;
	res.escape = context_backtick_escape;
	res.expansion = lexer_rule_expansion;
	res.is_expansion = is_expansion_context;
	res.is_end = is_context_backtick_ending;
	res.unescaped = context_backtick_unescape;
	return (res);
}

t_error	lexer_context_backtick(t_lexer *state)
{
	return (lexer_context_scan(state, context_backtick_rules()));
}
