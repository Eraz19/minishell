#include "scanner_recognition_.h"

bool	is_end(t_lexer *state)
{
	return (state->input->str.data[state->input->i] == '\0');
}

t_error	lexer_rule_end(t_lexer *state)
{
	lexer_delimit_token(state);
	if (state->token->type == TOKEN_NONE)
		state->token->type = TOKEN_EOF;
	return (state->err);
}
