/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arith.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:12:40 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 16:37:06 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lexer_backup.h"
#include "token_recognition.h"
#include "token_recognition_priv.h"
#include "token_recognition_context.h"
#include "token_recognition_context_scan.h"

t_error	arith_context_unescape_special(t_lexer *lexer, void *nesting_depth)
{
	char	current_char;

	current_char = lexer->input->str.data[lexer->input->i];
	if (current_char == '(')
	{
		(*((size_t *)nesting_depth))++;
		return (token_recognition_consume(lexer, lexer->token->type, 1));
	}
	else if (current_char == ')')
	{
		(*((size_t *)nesting_depth))--;
		return (token_recognition_consume(lexer, lexer->token->type, 1));
	}
	else
		return (token_recognition_consume(lexer, lexer->token->type, 1));
}

t_error	arith_context_escape_rules(t_lexer *lexer)
{
	t_token_recognition_escape	args;

	args.lexer = lexer;
	args.line_continuation = true;
	args.is_in_special_context = NULL;
	args.is_in_special_whitelist = NULL;
	args.is_in_whitelist = is_in_context_dquote_whitelist;
	return (scan_context_escape(args));
}

t_error	arith_context_unescape_rules(t_lexer *lexer, void *nesting_depth)
{
	t_token_recognition_unescape	args;

	args.lexer = lexer;
	args.special_args = nesting_depth;
	args.special_handler = arith_context_unescape_special;
	return (scan_context_unescape(args));
}

t_token_recognition_context	arith_context_rules(
						t_lexer *lexer,
						t_context_stack_item *item,
						size_t *nesting_depth)
{
	return ((t_token_recognition_context)
		{
			.lexer = lexer,
			.context_item = item,
			.opening_len = 3,
			.closing_len = 1,
			.quoting = NULL,
			.is_quoting = NULL,
			.expansion = recognize_token_expansion_context,
			.is_expansion = is_expansion_context_start,
			.unescaped_args = nesting_depth,
			.unescaped = arith_context_unescape_rules,
			.escape = arith_context_escape_rules,
			.is_end = is_context_arith_ending,
		}
	);
}

t_error	scan_arith_context(t_lexer *lexer)
{
	t_context_stack_item	*item;
	t_lexer_backup			backup;
	size_t					nesting_depth;

	nesting_depth = 0;
	backup = lexer_backup(lexer);
	lexer->err = context_stack_item_init(&item, CONTEXT_ARITH);
	if (lexer->err.type)
		return (lexer->err);
	lexer->err = context_stack_push(&lexer->token->contexts, item);
	if (lexer->err.type)
		return (free(item), lexer->err);
	if (scan_context(arith_context_rules(lexer, item, &nesting_depth)).type)
		return (lexer->err);
	if (lexer->input->str.data[lexer->input->i] != ')')
	{
		if (lexer_restore(lexer, backup).type)
			return (lexer->err);
		return (lexer->err = error(ERR_CTX_END_NOT_FOUND), lexer->err);
	}
	if (token_recognition_consume(lexer, lexer->token->type, 1).type)
		return (lexer->err);
	return (item->end = lexer->token->value.len - 1, lexer->err);
}
