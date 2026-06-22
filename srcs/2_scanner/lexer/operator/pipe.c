#include "lexer_operator_.h"

bool	is_operator_char_pipe(t_lexer *state)
{
	if (state->token->type == PIPE)
		return (true);
	else if (state->token->type == GREAT)
		return (true);
	else if (!is_in_middle_of_operator(state))
		return (true);
	return (false);
}

t_error	operator_add_pipe(t_lexer *state)
{
	if (state->token->type == PIPE)
		return (lexer_consume(state, OR_IF, 1));
	else if (state->token->type == GREAT)
		return (lexer_consume(state, CLOBBER, 1));
	else if (state->token->type == NONE)
		return (lexer_consume(state, PIPE, 1));
	return (state->err = error(ERR_INCOHERENT_STATE));
}
