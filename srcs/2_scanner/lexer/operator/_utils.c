#include "lexer_operator_.h"

bool	is_in_middle_of_operator(t_lexer *state)
{
	return (state->token->type != TOKEN_NONE
		&& state->token->type != TOKEN_TOKEN);
}
