#include "alias.h"
#include "shell.h"
#include "reader_.h"
#include "scanner_.h"
#include "scanner_recognition_.h"

static t_error	scanner_lexer_continuation(t_lexer *lexer)
{
	t_scanner	*scanner;
	t_string	last_input;
	size_t		last_input_i;
	t_string	continuation;

	lexer->err = reader_continuation(&lexer->input->str);
	if (lexer->err.type)
		return (lexer->err);
	scanner = shell_get_scanner();
	if (scanner == NULL)
		return (lexer->err = error(ERR_SHELL_NOT_FOUND));
	if (&(scanner->lexer) != lexer && scanner->lexer.input != NULL)
	{
		last_input = scanner->lexer.input->str;
		last_input_i = scanner->lexer.input->i;
		if (!string_init(&continuation, 0, last_input.data + last_input_i, -1))
			return (lexer->err = error_sys());
		last_input = scanner->lexer.input->str;
		if (!string_append(&last_input, &continuation))
			lexer->err = error_sys();
		string_free(&continuation);
	}
	return (lexer->err);
}

static t_error	scanner_lexer_on_input_end(t_lexer *lexer)
{
	return (lexer->err = alias_on_expansion_end());
}

t_lexer_rules	scanner_lexer_rules(t_scanner *scanner)
{
	t_lexer_rules	rules;

	rules.recognize = scanner_recognize;
	rules.on_input_end = scanner_lexer_on_input_end;
	if (scanner->mode == SCAN_MODE_STDIN_TTY)
		rules.on_eoi = scanner_lexer_continuation;
	else
		rules.on_eoi = NULL;
	return (rules);
}
