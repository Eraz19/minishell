/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dquote.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 14:21:55 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/01 11:16:59 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_context.h"
#include "../token/_token.h"

static bool	ctx_dquote_escape(t_lexer *state)
{
	t_escape_handler	args;

	args.is_in_special_context = NULL;
	args.is_in_special_whitelist = NULL;
	args.enable_line_continuation = true;
	args.is_in_whitelist = is_in_ctx_dquote_whitelist;
	return (ctx_escape(state, args));
}

static bool	ctx_dquote_unescape(t_lexer *state, void *_)
{
	t_unescape_handler	args;

	args.special_args = NULL;
	args.special_handler = NULL;
	return (ctx_unescape(state, args));
}

t_ctx_handler	ctx_dquote_rules(void)
{
	t_ctx_handler	res;

	res.quoting = NULL;
	res.opening_len = 1;
	res.ctx_mode = DQUOTE;
	res.unescaped_args = NULL;
	res.escape = ctx_dquote_escape;
	res.is_end = is_ctx_dquote_ending;
	res.unescaped = ctx_dquote_unescape;
	res.substitution = lexer_substitution;
	return (res);
}
