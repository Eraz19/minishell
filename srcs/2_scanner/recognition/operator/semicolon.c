#include "scanner_recognition_.h"

bool	is_operator_char_semicolon(t_lexer *state)
{
	if (state->token->type == TOKEN_SCOLON)
		return (true);
	else if (!is_in_middle_of_operator(state))
		return (true);
	return (false);
}

t_error	operator_add_semicolon(t_lexer *state)
{
	if (state->token->type == TOKEN_SCOLON)
		return (lexer_consume(state, TOKEN_DSEMI, 1));
	else if (state->token->type == TOKEN_NONE)
		return (lexer_consume(state, TOKEN_SCOLON, 1));
	return (state->err = error(ERR_INCOHERENT_STATE));
}
