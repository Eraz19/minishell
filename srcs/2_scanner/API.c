#include "shell.h"
#include "reader_.h"
#include "heredoc.h"
#include "scanner.h"
#include "scanner_.h"

t_error	scanner_get_next_token(t_token *token)
{
	t_scanner	*scanner;

	scanner = shell_get_scanner();
	if (scanner == NULL)
		return (scanner_error_qualify(error(ERR_SHELL_NOT_FOUND), false));
	if (scanner->lexer.input_stack.len == 0)
	{
		if (scanner_read_input(scanner).type)
			return (scanner->err
				= scanner_error_qualify(scanner->err, true));
		if (scanner->lexer.input_stack.len == 0)
			return (token_init(token), token->type = TOKEN_EOF, scanner->err);
	}
	if (lexer_get_next_token(&scanner->lexer, token,
			scanner_lexer_rules(scanner)).type)
	{
		scanner->err = scanner_error_qualify(scanner->lexer.err, false);
		return (scanner->err);
	}
	if (token->type == TOKEN_TOKEN)
		return (scanner->err = scanner_error_qualify(
					scanner_alias_expand(scanner, token), false));
	return (scanner->err);
}

t_error	scanner_report_io_here(t_string *out, t_token *delim, t_here_mode mode)
{
	t_scanner	*scanner;

	scanner = shell_get_scanner();
	if (scanner == NULL)
		return (scanner_error_qualify(error(ERR_SHELL_NOT_FOUND), false));
	scanner->err = scanner_error_qualify(
			heredoc_register(out, delim, mode), false);
	return (scanner->err);
}

t_error	scanner_heredoc_read(void)
{
	t_lexer_input_stack_item	*item;
	t_scanner					*scanner;

	scanner = shell_get_scanner();
	if (scanner == NULL)
		return (scanner_error_qualify(error(ERR_SHELL_NOT_FOUND), false));
	if (scanner->lexer.input == NULL)
		scanner->err = heredoc_read_body_from_input(NULL, NULL);
	else
	{
		item = scanner->lexer.input;
		scanner->err = heredoc_read_body_from_input(&item->str, &item->i);
	}
	scanner->err = scanner_error_qualify(scanner->err, false);
	return (scanner->err);
}

t_error	scanner_read_continuation(t_string *res)
{
	return (scanner_error_qualify(reader_continuation(res), true));
}
