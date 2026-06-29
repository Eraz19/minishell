#include "scanner_recognition_.h"

bool	is_comment(t_lexer *state)
{
	return (state->input->str.data[state->input->i] == '#');
}

void	lexer_rule_comment(t_lexer *state)
{
	while (state->input->str.data[state->input->i] != '\0' &&
		state->input->str.data[state->input->i] != '\n')
		state->input->i++;
}
