#include "lexer.h"

t_error	context_EOI(t_lexer *state)
{
	if (state->rules.on_eoi != NULL)
		return (state->rules.on_eoi(state));
	return (state->err = error(ERR_UNEXPECTED_EOI));
}

t_error	context_escape_next_char(t_lexer *state, t_escape_args args)
{
	bool	in_special_context;

	in_special_context = false;
	if (args.is_in_special_context != NULL)
		in_special_context = args.is_in_special_context(state);
	if (in_special_context && args.is_in_special_whitelist != NULL)
	{
		if (args.is_in_special_whitelist(
				state->input->str.data[state->input->i]))
			lexer_consume(state, state->token->type, 1);
	}
	else if (!in_special_context && args.is_in_whitelist != NULL)
	{
		if (args.is_in_whitelist(state->input->str.data[state->input->i]))
			lexer_consume(state, state->token->type, 1);
	}
	else
		state->err = error(ERR_INCOHERENT_STATE);
	return (state->err);
}
