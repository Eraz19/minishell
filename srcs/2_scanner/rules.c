#include "alias.h"
#include "reader_.h"
#include "scanner_.h"
#include "scanner_recognition_.h"

static t_error	scanner_lexer_continuation(t_lexer *state)
{
	return (state->err = reader_continuation(&state->input->str));
}

static t_error	scanner_lexer_on_input_end(t_lexer *state)
{
	return (state->err = alias_on_expansion_end());
}

t_lexer_rules	scanner_lexer_rules(t_scanner *state)
{
	t_lexer_rules	rules;

	rules.recognize = scanner_recognize;
	rules.on_input_end = scanner_lexer_on_input_end;
	if (state->mode == SCAN_STDIN_TTY)
		rules.on_eoi = scanner_lexer_continuation;
	else
		rules.on_eoi = NULL;
	return (rules);
}
