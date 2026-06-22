#include "lexer_rules_.h"

bool	is_comment(t_lexer *state)
{
	return (state->input->str[state->input->i] == '#');
}

void	lexer_rule_comment(t_lexer *state)
{
	while (state->input->str[state->input->i] != '\0' &&
		state->input->str[state->input->i] != '\n')
		state->input->i++;
}
