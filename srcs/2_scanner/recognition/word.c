#include "scanner_recognition_.h"

static t_error	context_top_level_escape(t_lexer *state)
{
	t_escape_args	args;

	args.is_in_special_context = NULL;
	args.is_in_special_whitelist = NULL;
	args.enable_line_continuation = true;
	args.is_in_whitelist = is_in_context_none_whitelist;
	return (lexer_context_escape(state, args));
}

bool	is_in_middle_of_word(t_lexer *state)
{
	return (state->token->type == TOKEN_TOKEN);
}

t_error	lexer_rule_in_middle_of_word(t_lexer *state)  // Rule 8
{
	if (state->input->str[state->input->i] == '\\')
		return (context_top_level_escape(state));
	else
	{
		if (state->input->str[state->input->i] == '='
			&& state->token->assignment_offset == -1)
			state->token->assignment_offset = (ssize_t)state->input->i;
		return (lexer_consume(state, TOKEN_TOKEN, 1));
	}
}

t_error	lexer_rule_new_word(t_lexer *state) // Rule 10
{
	if (state->input->str[state->input->i] == '\\')
		return (context_top_level_escape(state));
	else
		return (lexer_consume(state, TOKEN_TOKEN, 1));
}
