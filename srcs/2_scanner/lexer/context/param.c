/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 14:20:13 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/01 11:17:28 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_context.h"
#include "../token/_token.h"

static bool	ctx_param_escape(t_lexer *state)
{
	t_escape_handler	args;

	args.is_in_special_context = NULL;
	args.is_in_special_whitelist = NULL;
	args.enable_line_continuation = true;
	args.is_in_whitelist = is_in_ctx_param_whitelist;
	return (ctx_escape(state, args));
}

static bool	ctx_param_unescape(t_lexer *state, void *_)
{
	t_unescape_handler	args;

	args.special_args = NULL;
	args.special_handler = NULL;
	return (ctx_unescape(state, args));
}

t_ctx_handler	ctx_param_rules(void)
{
	t_ctx_handler	res;

	res.opening_len = 2;
	res.ctx_mode = PARAM;
	res.unescaped_args = NULL;
	res.quoting = lexer_quoting;
	res.escape = ctx_param_escape;
	res.is_end = is_ctx_param_ending;
	res.unescaped = ctx_param_unescape;
	res.substitution = lexer_substitution;
	return (res);
}
