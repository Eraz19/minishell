#include "scanner_recognition_.h"

bool	is_operator_char_pipe(t_lexer *state)
{
	if (state->token->type == TOKEN_PIPE)
		return (true);
	else if (state->token->type == TOKEN_GREAT)
		return (true);
	else if (!is_in_middle_of_operator(state))
		return (true);
	return (false);
}

t_error	operator_add_pipe(t_lexer *state)
{
	if (state->token->type == TOKEN_PIPE)
		return (lexer_consume(state, TOKEN_OR_IF, 1));
	else if (state->token->type == TOKEN_GREAT)
		return (lexer_consume(state, TOKEN_CLOBBER, 1));
	else if (state->token->type == TOKEN_NONE)
		return (lexer_consume(state, TOKEN_PIPE, 1));
	return (state->err = error(ERR_INCOHERENT_STATE));
}
