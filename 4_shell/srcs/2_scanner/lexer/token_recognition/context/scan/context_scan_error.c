/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_scan_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:12:18 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 16:52:33 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "token_recognition_context_scan_priv.h"

bool	has_innermost_unterminated_context(t_context *out, t_token *token)
{
	size_t					i;
	t_context_stack_item	*item;

	i = token->contexts.len;
	while (i > 0)
	{
		--i;
		context_stack_get(&token->contexts, &item, i);
		if (item->end == SIZE_MAX)
			return (*out = item->context, true);
	}
	return (false);
}

bool	get_message_on_unterminated_context(const char **out, t_lexer *lexer)
{
	t_context	context;

	if (!has_innermost_unterminated_context(&context, lexer->token))
		return (false);
	if (context == CONTEXT_SQUOTE)
		return (*out = "unterminated single quotes", true);
	else if (context == CONTEXT_DQUOTE)
		return (*out = "unterminated double quotes", true);
	else if (context == CONTEXT_DOLLAR_SQUOTE)
		return (*out = "unterminated $'...' quotes", true);
	else if (context == CONTEXT_BACKTICK)
		return (*out = "unterminated backquote substitution", true);
	else if (context == CONTEXT_CMD_SUB)
		return (*out = "unterminated command substitution", true);
	else if (context == CONTEXT_ARITH)
		return (*out = "unterminated arithmetic expansion", true);
	else if (context == CONTEXT_PARAM)
		return (*out = "unterminated parameter expansion", true);
	else
		return (*out = "unterminated unknown context", true);
}

t_error	error_unterminated_construct(t_lexer *lexer)
{
	const char	*error_message;

	if (!get_message_on_unterminated_context(&error_message, lexer))
		error_message = "unexpected end of input";
	error_print(error(ERR_POSIX_SYNTAX), "scanner", error_message, NULL, NULL);
	env_set_last_status((int)ERR_POSIX_SYNTAX);
	lexer->err.printed = true;
	return (lexer->err);
}
