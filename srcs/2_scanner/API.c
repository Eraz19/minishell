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
		return (error(ERR_INTERNAL));
	if (scanner->lexer.input_stack.len == 0 && scanner_read_input(scanner).type)
		return (scanner->err);
	if (lexer_get_next_token(&scanner->lexer, token,
			scanner_lexer_rules(scanner)).type)
		return (scanner->err = scanner->lexer.err, scanner->err);
	if (token->type == TOKEN_TOKEN)
		return (scanner_alias_expand(scanner, token));
	return (scanner->err);
}

t_error	scanner_report_io_here(t_string *out, t_token *delim, t_here_mode mode)
{
	t_scanner	*scanner;

	scanner = shell_get_scanner();
	if (scanner == NULL)
		return (error(ERR_INTERNAL));
	scanner->err = heredoc_register(out, delim, mode);
	return (scanner->err);
}

t_error	scanner_heredoc_read(void)
{
	t_lexer_input_stack_item	*item;
	t_scanner					*scanner;

	scanner = shell_get_scanner();
	if (scanner == NULL)
		return (error(ERR_INTERNAL));
	if (scanner->lexer.input == NULL)
		scanner->err = heredoc_read_body_from_input(NULL, NULL);
	else
	{
		item = scanner->lexer.input;
		scanner->err = heredoc_read_body_from_input(&item->str, &item->i);
	}
	return (scanner->err);
}

t_error	scanner_read_continuation(t_string *res)
{
	return (reader_continuation(res));
}
