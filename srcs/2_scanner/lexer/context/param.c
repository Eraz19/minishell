/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 14:20:13 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/10 16:51:30 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_rules_.h"
#include "lexer_context_.h"

static t_error	context_param_escape(t_lexer *state)
{
	t_escape_args	args;

	args.is_in_special_context = NULL;
	args.is_in_special_whitelist = NULL;
	args.enable_line_continuation = true;
	args.is_in_whitelist = is_in_context_param_whitelist;
	return (lexer_context_escape(state, args));
}

static t_error	context_param_unescape(t_lexer *state, void *_)
{
	t_unescape_args	args;

	args.special_args = NULL;
	args.special_handler = NULL;
	return (lexer_context_unescape(state, args));
}

static t_context_args	context_param_rules(void)
{
	t_context_args	res;

	res.opening_len = 2;
	res.context = PARAM;
	res.unescaped_args = NULL;
	res.quoting = lexer_rule_quoting;
	res.escape = context_param_escape;
	res.is_quoting = is_quoting_context;
	res.is_end = is_context_param_ending;
	res.expansion = lexer_rule_expansion;
	res.unescaped = context_param_unescape;
	res.is_expansion = is_expansion_context;
	return (res);
}

t_error	lexer_context_param(t_lexer *state)
{
	return (lexer_context_scan(state, context_param_rules()));
}
