/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_scan_escape.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:12:20 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 16:52:07 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h> // DEBUG
#include "token_recognition_priv.h"
#include "token_recognition_context_scan.h"
#include "token_recognition_context_scan_priv.h"

t_error	scan_escape_default_context(t_token_recognition_escape args)
{
	t_token_type	type;
	char			current_char;

	type = args.lexer->token->type;
	current_char = args.lexer->input->str.data[args.lexer->input->i];
	if (args.is_in_whitelist(current_char))
		token_recognition_consume(args.lexer, type, 1);
	return (args.lexer->err);
}

t_error	scan_escape_special_context(t_token_recognition_escape args)
{
	t_token_type	type;
	char			current_char;

	type = args.lexer->token->type;
	current_char = args.lexer->input->str.data[args.lexer->input->i];
	if (args.is_in_special_whitelist(current_char))
		token_recognition_consume(args.lexer, type, 1);
	return (args.lexer->err);
}

t_error	scan_context_escape_next_char(t_token_recognition_escape args)
{
	bool	in_special_context;

	in_special_context = false;
	if (args.lexer->input->str.data[args.lexer->input->i] == '\0')
		return (args.lexer->err);
	if (args.is_in_special_context != NULL)
		in_special_context = args.is_in_special_context(args.lexer);
	if (in_special_context && args.is_in_special_whitelist != NULL)
		return (scan_escape_special_context(args));
	else if (!in_special_context && args.is_in_whitelist != NULL)
		return (scan_escape_default_context(args));
	assert(false);
	return (args.lexer->err);
}

t_error	scan_context_line_continuation(t_token_recognition_escape args)
{
	char	current_char;

	token_recognition_advance(args.lexer, 2);
	current_char = args.lexer->input->str.data[args.lexer->input->i];
	if (current_char == '\0')
		return (on_context_scan_eoi(args.lexer));
	return (args.lexer->err);
}

t_error	scan_context_escape(t_token_recognition_escape args)
{
	t_token_type	type;
	char			*current_char;

	current_char = args.lexer->input->str.data + args.lexer->input->i;
	if (args.line_continuation && *(current_char + 1) == '\n')
		return (scan_context_line_continuation(args));
	else if (*current_char == '\0')
		return (on_context_scan_eoi(args.lexer));
	else
	{
		type = TOKEN_TOKEN;
		args.lexer->token->type = type;
		if (token_recognition_consume(args.lexer, type, 1).type)
			return (args.lexer->err);
		if (scan_context_escape_next_char(args).type)
			return (args.lexer->err);
	}
	return (args.lexer->err);
}
