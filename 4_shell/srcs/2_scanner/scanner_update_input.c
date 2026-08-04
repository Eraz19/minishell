/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_update_input.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:15:27 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 16:59:05 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader.h"
#include "scanner.h"
#include "options.h"
#include "scanner_priv.h"
#include "lexer_input_stack.h"

t_error	update_input_file(t_scanner *scanner, t_lexer_input_stack_item *out)
{
	scanner->err = reader_read_file(&out->str, scanner->source);
	if (scanner->err.type)
		return (scanner->err);
	return (scanner->err);
}

t_error	update_input_string(t_scanner *scanner, t_lexer_input_stack_item *out)
{
	if (!string_init(&out->str, 0, scanner->source, -1))
		return (scanner->err = error_sys());
	return (scanner->err);
}

t_error	update_input_stdin(t_scanner *scanner, t_lexer_input_stack_item *out)
{
	bool	is_interactive;

	scanner->err = option_is_active(OPT_INTERACTIVE, &is_interactive);
	if (scanner->err.type)
		return (scanner->err);
	else if (is_interactive == true)
		return (scanner->err = reader_read_ps1(&out->str));
	else
		return (scanner->err = reader_read_stdin(&out->str));
}

t_error	update_input_dispatch(t_scanner *scanner)
{
	t_lexer_input_stack_item	new_input;
	t_lexer_input_stack			*input_stack;

	lexer_input_stack_item_init(&new_input);
	if (scanner->mode == SCAN_MODE_FILE)
		update_input_file(scanner, &new_input);
	else if (scanner->mode == SCAN_MODE_STRING)
		update_input_string(scanner, &new_input);
	else if (scanner->mode == SCAN_MODE_STDIN)
		update_input_stdin(scanner, &new_input);
	if (scanner->err.type)
		return (lexer_input_stack_item_free(&new_input), scanner->err);
	input_stack = &scanner->lexer.input_stack;
	scanner->err = lexer_input_stack_push(input_stack, &new_input);
	return (scanner->err);
}

t_error	update_input(t_scanner *scanner, t_token *out, bool ps2)
{
	if (ps2)
	{
		scanner->err = read_and_propagate_ps2(scanner);
		return (requalify_scanner_error(scanner));
	}
	else if (scanner->lexer.input_stack.len == 0)
	{
		if (update_input_dispatch(scanner).type)
			return (requalify_scanner_error(scanner));
		if (scanner->lexer.input_stack.len == 0)
			return (token_init(out), out->type = TOKEN_EOF, scanner->err);
	}
	return (scanner->err);
}
