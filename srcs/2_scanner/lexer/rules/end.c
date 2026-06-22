#include "lexer_rules_.h"

bool	is_end(t_lexer *state)
{
	return (state->input->str[state->input->i] == '\0');
}

t_error	lexer_rule_end(t_lexer *state)
{
	if (state->token->type != NONE)
		return (lexer_delimit_token(state), state->err);
	else
		return (state->reached_EOI = true, state->err);
}
