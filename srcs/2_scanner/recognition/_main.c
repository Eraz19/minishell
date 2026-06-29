#include "scanner_recognition_.h"

t_error	scanner_recognize(t_lexer *state, t_context *context)
{
	if (is_end(state))
		return (lexer_rule_end(state));
	else if (is_in_middle_of_operator(state))
		return (lexer_rule_in_middle_of_operator(state));
	else if (is_quoting_context(
			state->input->str.data + state->input->i, context))
		return (lexer_rule_quoting(state, *context));
	else if (is_expansion_context(
			state->input->str.data + state->input->i, context))
		return (lexer_rule_expansion(state, *context));
	else if (is_new_operator(state))
		return (lexer_rule_new_operator(state));
	else if (is_blank(state->input->str.data[state->input->i]))
		return (lexer_rule_blank(state));
	else if (is_in_middle_of_word(state))
		return (lexer_rule_in_middle_of_word(state));
	else if (is_comment(state))
		return (lexer_rule_comment(state), state->err);
	else
		return (lexer_rule_new_word(state));
}
