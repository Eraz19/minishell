#include "lexer_operator_.h"

bool	is_operator_char_great(t_lexer *state)
{
	if (state->token->type == LESS)
		return (true);
	else if (state->token->type == GREAT)
		return (true);
	else if (!is_in_middle_of_operator(state))
		return (true);
	return (false);
}

t_error	operator_add_great(t_lexer *state)
{
	if (state->token->type == LESS)
		return (lexer_consume(state, LESSGREAT, 1));
	else if (state->token->type == GREAT)
		return (lexer_consume(state, DGREAT, 1));
	else if (state->token->type == NONE)
		return (lexer_consume(state, GREAT, 1));
	return (state->err = error(ERR_INCOHERENT_STATE));
}
