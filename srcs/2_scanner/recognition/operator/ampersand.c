#include "scanner_recognition_.h"

bool	is_operator_char_ampersand(t_lexer *state)
{
	if (state->token->type == TOKEN_SCOLON)
		return (true);
	else if (state->token->type == TOKEN_AMPERSAND)
		return (true);
	else if (state->token->type == TOKEN_LESS)
		return (true);
	else if (state->token->type == TOKEN_GREAT)
		return (true);
	else if (!is_in_middle_of_operator(state))
		return (true);
	return (false);
}

t_error	operator_add_ampersand(t_lexer *state)
{
	if (state->token->type == TOKEN_SCOLON)
		return (lexer_consume(state, TOKEN_SEMI_AND, 1));
	else if (state->token->type == TOKEN_AMPERSAND)
		return (lexer_consume(state, TOKEN_AND_IF, 1));
	else if (state->token->type == TOKEN_LESS)
		return (lexer_consume(state, TOKEN_LESSAND, 1));
	else if (state->token->type == TOKEN_GREAT)
		return (lexer_consume(state, TOKEN_GREATAND, 1));
	else if (state->token->type == TOKEN_NONE)
		return (lexer_consume(state, TOKEN_AMPERSAND, 1));
	return (state->err = error(ERR_INCOHERENT_STATE));
}
