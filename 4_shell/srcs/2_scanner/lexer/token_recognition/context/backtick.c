/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtick.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:12:43 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 16:49:42 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "token_recognition.h"
#include "token_recognition_priv.h"
#include "token_recognition_context.h"
#include "token_recognition_context_scan.h"

bool	is_backtick_dquote_surrounded(t_lexer *lexer)
{
	size_t					i;
	t_context_stack_item	*item;

	i = lexer->token->contexts.len;
	if (i > 0)
		--i;
	while (i > 0)
	{
		context_stack_get(&lexer->token->contexts, &item, --i);
		if (item->end != SIZE_MAX)
			continue ;
		return (item->context == CONTEXT_DQUOTE
			|| item->context == CONTEXT_ARITH);
	}
	return (false);
}

t_error	backtick_context_escape_rules(t_lexer *lexer)
{
	t_token_recognition_escape	args;

	args.lexer = lexer;
	args.line_continuation = is_backtick_dquote_surrounded(lexer);
	args.is_in_whitelist = is_in_context_backtick_whitelist;
	args.is_in_special_context = is_backtick_dquote_surrounded;
	args.is_in_special_whitelist = is_in_context_backtick_special_whitelist;
	return (scan_context_escape(args));
}

t_error	backtick_context_unescape_rules(t_lexer *lexer, void *_)
{
	t_token_recognition_unescape	args;

	(void)_;
	args.lexer = lexer;
	args.special_args = NULL;
	args.special_handler = NULL;
	return (scan_context_unescape(args));
}

t_token_recognition_context	backtick_context_rules(
								t_lexer *lexer,
								t_context_stack_item *item)
{
	return ((t_token_recognition_context)
		{
			.lexer = lexer,
			.context_item = item,
			.opening_len = 1,
			.closing_len = 1,
			.quoting = recognize_token_quoting_context,
			.is_quoting = is_quoting_context_start,
			.expansion = recognize_token_expansion_context,
			.is_expansion = is_expansion_context_start,
			.unescaped_args = NULL,
			.unescaped = backtick_context_unescape_rules,
			.escape = backtick_context_escape_rules,
			.is_end = is_context_backtick_ending,
		}
	);
}

t_error	scan_backtick_context(t_lexer *lexer)
{
	t_context_stack_item	*item;

	lexer->err = context_stack_item_init(&item, CONTEXT_BACKTICK);
	if (lexer->err.type)
		return (lexer->err);
	lexer->err = context_stack_push(&lexer->token->contexts, item);
	if (lexer->err.type)
		return (free(item), lexer->err);
	return (scan_context(backtick_context_rules(lexer, item)));
}
