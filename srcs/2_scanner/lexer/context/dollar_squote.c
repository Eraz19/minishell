/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_squote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 14:21:36 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/01 11:16:35 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_context.h"

static bool	ctx_dollar_squote_escape(t_lexer *state)
{
	t_escape_handler	args;

	args.is_in_special_context = NULL;
	args.is_in_special_whitelist = NULL;
	args.enable_line_continuation = false;
	args.is_in_whitelist = is_in_ctx_dollar_squote_whitelist;
	return (ctx_escape(state, args));
}

static bool	ctx_dollar_squote_unescape(t_lexer *state, void *_)
{
	t_unescape_handler	args;

	args.special_args = NULL;
	args.special_handler = NULL;
	return (ctx_unescape(state, args));
}

t_ctx_handler	ctx_dollar_squote_rules(void)
{
	t_ctx_handler	res;

	res.quoting = NULL;
	res.opening_len = 2;
	res.substitution = NULL;
	res.unescaped_args = NULL;
	res.ctx_mode = DOLLAR_SQUOTE;
	res.escape = ctx_dollar_squote_escape;
	res.is_end = is_ctx_dollar_squote_ending;
	res.unescaped = ctx_dollar_squote_unescape;
	return (res);
}
