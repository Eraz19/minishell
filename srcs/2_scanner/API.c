#include "heredoc.h"
#include "reader_.h"
#include "scanner.h"
#include "scanner_.h"

t_error	scanner_get_next_token(
			t_scanner *scanner,
			t_token *token,
			bool continuation)
{
	t_lexer_rules	lexer_rules;

	if (continuation == true)
	{
		scanner->err = scanner_lexer_continuation(&scanner->lexer);
		if (scanner->err.type)
			return (scanner->err = scanner_error_qualify(scanner->err, false));
	}
	else if (scanner->lexer.input_stack.len == 0)
		{
			if (scanner_read_input(scanner).type)
				return (scanner->err = scanner_error_qualify(scanner->err, true));
			if (scanner->lexer.input_stack.len == 0)
				return (token_init(token), token->type = TOKEN_EOF, scanner->err);
		}
	lexer_rules = scanner_lexer_rules();
	if (lexer_get_next_token(&scanner->lexer, token, lexer_rules).type)
		return (scanner->err = scanner_error_qualify(scanner->lexer.err, false));
	if (token->type == TOKEN_TOKEN)
	{
		scanner_alias_expand(scanner, token);
		return (scanner->err = scanner_error_qualify(scanner->err, false));
	}
	return (scanner->err);
}

t_error	scanner_read_heredoc(
			t_scanner *scanner,
			t_string *out,
			t_token *delim,
			bool strip)
{
	t_heredoc_read_args	args;
	t_string			delim_exp;

	scanner->err = heredoc_expand_delim(&delim_exp, delim);
	if (scanner->err.type)
		return (scanner->err = scanner_error_qualify(scanner->err, false));
	prepare_heredoc_read_args(scanner, &args, strip, &delim_exp);
	scanner->err = heredoc_read_body_from_input(out, &args);
	scanner->err = scanner_error_qualify(scanner->err, false);
	return (string_free(&delim_exp), scanner->err);
}

t_error	scanner_lexer_continuation(t_lexer *lexer)
{
	//t_scanner	*scanner;
	//t_string	last_input;
	//size_t		last_input_i;
	//t_string	continuation;

	fprintf(stderr, "[%s()]\n", __func__);
	if (lexer->scanner->mode != SCAN_MODE_CMD_SUB
		&& lexer->scanner->mode != SCAN_MODE_STDIN)
		return (error_print(error(ERR_POSIX_SYNTAX), NULL, NULL));
	lexer->err = reader_continuation(&lexer->input->str);
	if (lexer->err.type == ERR_VEOF)
		return (error_print(error(ERR_POSIX_SYNTAX), NULL, NULL));
	if (lexer->err.type)
		return (lexer->err);
	// ---- Make this continuation spread in parents
	
	// TODO Forward_continuation to parents 


	//last_input = scanner->lexer.input->str;
	//last_input_i = scanner->lexer.input->i;
	//if (!string_init(&continuation, 0, last_input.data + last_input_i, -1))
	//	return (lexer->err = error_sys());
	//last_input = scanner->lexer.input->str;
	//if (!string_append(&last_input, &continuation))
	//	lexer->err = error_sys();
	//string_free(&continuation);

	// ---------
	return (lexer->err);
}

void	scanner_set_input(t_scanner *scanner, const char *input)
{
	lexer_clear(&scanner->lexer);
	scanner->source = input;
}

