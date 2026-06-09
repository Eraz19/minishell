/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_squote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 14:21:36 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/05 20:11:36 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "__lexer_context.h"

static t_error	context_dollar_squote_escape(t_lexer *state)
{
	t_escape_args	args;

	args.is_in_special_context = NULL;
	args.is_in_special_whitelist = NULL;
	args.enable_line_continuation = false;
	args.is_in_whitelist = is_in_context_dollar_squote_whitelist;
	return (context_escape(state, args));
}

static t_error	context_dollar_squote_unescape(t_lexer *state, void *_)
{
	t_unescape_args	args;

	args.special_args = NULL;
	args.special_handler = NULL;
	return (context_unescape(state, args));
}

static t_context_args	context_dollar_squote_rules(void)
{
	t_context_args	res;

	res.quoting = NULL;
	res.opening_len = 2;
	res.is_quoting = NULL;
	res.expansion = NULL;
	res.unescaped_args = NULL;
	res.is_expansion = NULL;
	res.context = DOLLAR_SQUOTE;
	res.escape = context_dollar_squote_escape;
	res.is_end = is_context_dollar_squote_ending;
	res.unescaped = context_dollar_squote_unescape;
	return (res);
}

t_error	context_dollar_squote(t_lexer *state)
{
	return (context_scan(state, context_dollar_squote_rules()));
}
