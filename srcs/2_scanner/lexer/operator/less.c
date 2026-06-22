#include "lexer_operator_.h"

bool	is_operator_char_less(t_lexer *state)
{
	if (state->token->type == LESS)
		return (true);
	else if (!is_in_middle_of_operator(state))
		return (true);
	return (false);
}

t_error	operator_add_less(t_lexer *state)
{
	if (state->token->type == LESS)
		return (lexer_consume(state, DLESS, 1));
	else if (state->token->type == NONE)
		return (lexer_consume(state, LESS, 1));
	return (state->err = error(ERR_INCOHERENT_STATE));
}
