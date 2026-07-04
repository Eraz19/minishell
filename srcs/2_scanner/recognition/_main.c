#include "scanner_recognition_.h"

t_error	scanner_recognize(t_lexer *lexer, t_context *context)
{
	if (is_end(lexer))
		return (lexer_rule_end(lexer));
	else if (is_in_middle_of_operator(lexer))
		return (lexer_rule_in_middle_of_operator(lexer));
	else if (is_quoting_context(
			lexer->input->str.data + lexer->input->i, context))
		return (lexer_rule_quoting(lexer, *context));
	else if (is_substitution_context(
			lexer->input->str.data + lexer->input->i, context))
		return (lexer_rule_expansion(lexer, *context));
	else if (is_new_operator(lexer))
		return (lexer_rule_new_operator(lexer));
	else if (is_blank(lexer->input->str.data[lexer->input->i]))
		return (lexer_rule_blank(lexer));
	else if (is_in_middle_of_word(lexer))
		return (lexer_rule_in_middle_of_word(lexer));
	else if (is_comment(lexer))
		return (lexer_rule_comment(lexer), lexer->err);
	else
		return (lexer_rule_new_word(lexer));
}
