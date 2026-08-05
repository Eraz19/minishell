/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _API.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:15:09 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/05 18:18:59 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "scanner.h"
#include "scanner_priv.h"
#include "token_recognition_context.h"

t_error	scanner_get_next_token(t_scanner *scanner, t_token *out, bool ps2)
{
	if (update_input(scanner, out, ps2).type)
		return (lexer_unbind_token(&scanner->lexer), scanner->err);
	scanner->err = lexer_get_next_token(&scanner->lexer, out);
	if (scanner->err.type)
		scanner->err = requalify_scanner_error(scanner);
	else if (out->type == TOKEN_TOKEN)
		scanner->err = expand_alias(scanner, out);
	lexer_unbind_token(&scanner->lexer);
	return (requalify_scanner_error(scanner));
}

t_error	scanner_read_heredoc(
			t_scanner *scanner,
			t_string *out,
			t_token *delim,
			bool strip)
{
	scanner->err = heredoc_read_body(&scanner->lexer, out, delim, strip);
	return (requalify_scanner_error(scanner));
}

t_error	scanner_scan_word(
			t_scanner *scanner,
			t_token *out,
			t_token_recognition_context args)
{
	if (update_input(scanner, out, false).type)
		return (lexer_unbind_token(&scanner->lexer), scanner->err);
	scanner->err = context_stack_item_init(&args.context_item, CONTEXT_NONE);
	if (scanner->err.type == ERR_NO)
		scanner->err = lexer_scan_word(&scanner->lexer, out, &args);
	lexer_unbind_token(&scanner->lexer);
	return (requalify_scanner_error(scanner));
}

t_error	scanner_bind_input(t_scanner *scanner, const char *cmd_string)
{
	t_lexer_input_stack	*input_stack;
	t_lexer_input_stack	*parent_input_stack;

	lexer_clear(&scanner->lexer);
	scanner->source = cmd_string;
	if (scanner->mode == SCAN_MODE_CMD_SUB)
	{
		input_stack = &scanner->lexer.input_stack;
		parent_input_stack = &scanner->parent_scanner->lexer.input_stack;
		scanner->err = lexer_input_stack_dup(input_stack, parent_input_stack);
	}
	return (requalify_scanner_error(scanner));
}
