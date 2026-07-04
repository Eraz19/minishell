#include "scanner_recognition_.h"

static bool	is_next_char_redirection(t_lexer *lexer)
{
	return (lexer->input->str.data[lexer->input->i] == '>' ||
		lexer->input->str.data[lexer->input->i] == '<');
}

static bool	is_token_io_number(t_lexer *lexer)
{
	int		io_number;

	if (is_next_char_redirection(lexer))
	{
		return (parse_int(lexer->token->value.data, &io_number));
	}
	return (false);
}

bool	is_new_operator(t_lexer *lexer)
{
	return (!is_in_middle_of_operator(lexer) && is_operator_char(lexer));
}

t_error	lexer_rule_in_middle_of_operator(t_lexer *lexer) // Rule 2-3
{
	if (is_operator_char(lexer)) // Rule 2
		return (lexer_add_char_into_token_operator(lexer), lexer->err);
	else
		return (lexer_delimit_token(lexer), lexer->err); // Rule 3
}

t_error	lexer_rule_new_operator(t_lexer *lexer) // Rule 6
{
	if (lexer->token->type != TOKEN_NONE)
	{
		if (is_token_io_number(lexer))
			lexer->token->type = TOKEN_IO_NUMBER;
		if (lexer->err.type)
			return (lexer->err);
		else
			return (lexer_delimit_token(lexer), lexer->err);
	}
	else
		return (lexer_add_char_into_token_operator(lexer), lexer->err);
}
