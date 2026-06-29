#include "scanner_recognition_.h"

bool	is_operator_char(t_lexer *state)
{
	const char	*input_ptr;

	input_ptr = state->input->str.data + state->input->i;
	if (input_ptr[0] == '\n' && !is_in_middle_of_operator(state))
		return (true);
	else if (input_ptr[0] == '(' && !is_in_middle_of_operator(state))
		return (true);
	else if (input_ptr[0] == ')' && !is_in_middle_of_operator(state))
		return (true);
	else if (input_ptr[0] == ';')
		return (is_operator_char_semicolon(state));
	else if (input_ptr[0] == '&')
		return (is_operator_char_ampersand(state));
	else if (input_ptr[0] == '|')
		return (is_operator_char_pipe(state));
	else if (input_ptr[0] == '<')
		return (is_operator_char_less(state));
	else if (input_ptr[0] == '>')
		return (is_operator_char_great(state));
	else if (input_ptr[0] == '-' && state->token->type == TOKEN_DLESS)
		return (true);
	return (false);
}

t_error	lexer_add_char_into_token_operator(t_lexer *state)
{
	const char	*input_ptr;

	input_ptr = state->input->str.data + state->input->i;
	if (input_ptr[0] == '\n')
		return (lexer_consume(state, TOKEN_NEWLINE, 1));
	else if (input_ptr[0] == '(')
		return (lexer_consume(state, TOKEN_LPARENTHESIS, 1));
	else if (input_ptr[0] == ')')
		return (lexer_consume(state, TOKEN_RPARENTHESIS, 1));
	else if (input_ptr[0] == ';')
		return (operator_add_semicolon(state));
	else if (input_ptr[0] == '&')
		return (operator_add_ampersand(state));
	else if (input_ptr[0] == '|')
		return (operator_add_pipe(state));
	else if (input_ptr[0] == '<')
		return (operator_add_less(state));
	else if (input_ptr[0] == '>')
		return (operator_add_great(state));
	else if (input_ptr[0] == '-')
		return (lexer_consume(state, TOKEN_DLESSDASH, 1));
	return (state->err = error(ERR_INCOHERENT_STATE));
}
