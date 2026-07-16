#include "shell.h"
#include "heredoc.h"
#include "scanner.h"
#include "scanner_.h"

t_error	scanner_get_next_token(t_token *token)
{
	t_scanner		*scanner;
	t_lexer_rules	lexer_rules;

	scanner = shell_get_scanner();
	if (scanner == NULL)
		return (scanner_error_qualify(error(ERR_SHELL_NOT_FOUND), false));
	if (scanner->lexer.input_stack.len == 0)
	{
		if (scanner_read_input(scanner).type)
			return (scanner->err = scanner_error_qualify(scanner->err, true));
		if (scanner->lexer.input_stack.len == 0)
			return (token_init(token), token->type = TOKEN_EOF, scanner->err);
	}
	lexer_rules = scanner_lexer_rules(scanner);
	if (lexer_get_next_token(&scanner->lexer, token, lexer_rules).type)
	{
		scanner->err = scanner_error_qualify(scanner->lexer.err, false);
		return (scanner->err);
	}
	if (token->type == TOKEN_TOKEN)
	{
		scanner_alias_expand(scanner, token);
		return (scanner->err = scanner_error_qualify(scanner->err, false));
	}
	return (scanner->err);
}

t_error	scanner_read_heredoc(t_string *out, const t_token *delim, bool strip)
{
	t_heredoc_read_args	args;
	t_scanner			*scanner;
	t_string			delim_exp;

	scanner = shell_get_scanner();
	if (scanner == NULL)
		return (scanner_error_qualify(error(ERR_SHELL_NOT_FOUND), false));
	scanner->err = heredoc_expand_delim(&delim_exp, delim);
	if (scanner->err.type)
		return (scanner->err = scanner_error_qualify(scanner->err, false));
	prepare_heredoc_read_args(scanner, &args, strip, &delim_exp);
	scanner->err = heredoc_read_body_from_input(out, &args);
	scanner->err = scanner_error_qualify(scanner->err, false);
	return (string_free(&delim_exp), scanner->err);
}
