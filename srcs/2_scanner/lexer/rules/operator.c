#include <stdlib.h>
#include "lexer_rules_.h"
#include "lexer_operator_.h"

static bool	is_next_char_redirection(t_lexer *state)
{
	return (state->input->str[state->input->i] == '>' ||
		state->input->str[state->input->i] == '<');
}

static bool	is_token_io_number(t_lexer *state)
{
	int		io_number;
	char	*token_str;

	if (is_next_char_redirection(state))
	{
		token_str = buff_get_string(&state->token->value);
		if (token_str == NULL)
			return (state->err = error_sys(), false);
		if (!parse_int(token_str, &io_number))
			return (free(token_str), false);
		return (free(token_str), true);
	}
	return (false);
}

bool	is_new_operator(t_lexer *state)
{
	return (!is_in_middle_of_operator(state) && is_operator_char(state));
}

t_error	lexer_rule_in_middle_of_operator(t_lexer *state) // Rule 2-3
{
	if (is_operator_char(state)) // Rule 2
		return (lexer_add_char_into_token_operator(state), state->err);
	else
		return (lexer_delimit_token(state), state->err); // Rule 3
}

t_error	lexer_rule_new_operator(t_lexer *state) // Rule 6
{
	if (state->token->type != NONE)
	{
		if (is_token_io_number(state))
			state->token->type = IO_NUMBER;
		if (state->err.type)
			return (state->err);
		else
			return (lexer_delimit_token(state), state->err);
	}
	else
		return (lexer_add_char_into_token_operator(state), state->err);
}
