#include "scanner_recognition_.h"

t_error	lexer_rule_blank(t_lexer *state)
{
	if (state->token->type != TOKEN_NONE)
		return (lexer_delimit_token(state), state->err);
	while (is_blank(state->input->str.data[state->input->i]) &&
		state->input->str.data[state->input->i] != '\0')
		state->input->i++;
	return (state->err);
}
