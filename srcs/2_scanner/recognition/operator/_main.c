#include "scanner_recognition_.h"

bool	is_operator_char(t_lexer *lexer)
{
	const char	*input_ptr;

	input_ptr = lexer->input->str.data + lexer->input->i;
	if (input_ptr[0] == '\n' && !is_in_middle_of_operator(lexer))
		return (true);
	else if (input_ptr[0] == '(' && !is_in_middle_of_operator(lexer))
		return (true);
	else if (input_ptr[0] == ')' && !is_in_middle_of_operator(lexer))
		return (true);
	else if (input_ptr[0] == ';')
		return (is_operator_char_semicolon(lexer));
	else if (input_ptr[0] == '&')
		return (is_operator_char_ampersand(lexer));
	else if (input_ptr[0] == '|')
		return (is_operator_char_pipe(lexer));
	else if (input_ptr[0] == '<')
		return (is_operator_char_less(lexer));
	else if (input_ptr[0] == '>')
		return (is_operator_char_great(lexer));
	else if (input_ptr[0] == '-' && lexer->token->type == TOKEN_DLESS)
		return (true);
	return (false);
}

t_error	lexer_add_char_into_token_operator(t_lexer *lexer)
{
	const char	*input_ptr;

	input_ptr = lexer->input->str.data + lexer->input->i;
	if (input_ptr[0] == '\n')
		return (lexer_consume(lexer, TOKEN_NEWLINE, 1));
	else if (input_ptr[0] == '(')
		return (lexer_consume(lexer, TOKEN_LPARENTHESIS, 1));
	else if (input_ptr[0] == ')')
		return (lexer_consume(lexer, TOKEN_RPARENTHESIS, 1));
	else if (input_ptr[0] == ';')
		return (operator_add_semicolon(lexer));
	else if (input_ptr[0] == '&')
		return (operator_add_ampersand(lexer));
	else if (input_ptr[0] == '|')
		return (operator_add_pipe(lexer));
	else if (input_ptr[0] == '<')
		return (operator_add_less(lexer));
	else if (input_ptr[0] == '>')
		return (operator_add_great(lexer));
	else if (input_ptr[0] == '-')
		return (lexer_consume(lexer, TOKEN_DLESSDASH, 1));
	return (lexer->err = error(ERR_INCOHERENT_STATE));
}
