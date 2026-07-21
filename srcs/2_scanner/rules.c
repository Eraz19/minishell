#include "alias.h"
#include "scanner_.h"
#include "scanner_recognition_.h"

static t_error	scanner_lexer_on_input_end(t_lexer *lexer)
{
	return (lexer->err = alias_on_expansion_end());
}

t_lexer_rules	scanner_lexer_rules()
{
	t_lexer_rules	rules;

	rules.recognize = scanner_recognize;
	rules.on_input_end = scanner_lexer_on_input_end;
	return (rules);
}
