#include "shell.h"
#include "utils.h"
#include "scanner.h"

t_error	scanner_init(t_scanner *state)
{
	*state = (t_scanner){0};
	lexer_init(&state->lexer);
	return (error(ERR_NO));
}

void	scanner_free(t_scanner *state)
{
	lexer_free(&state->lexer);
	*state = (t_scanner){0};
}

t_error	scanner_load(t_scanner *state, const char *source)
{
	t_error	err;

	state->mode = SCAN_NONE;
	err = scan_set_mode(&state->mode);
	if (err.type != ERR_NO)
		return (err);
	if (state->mode == SCAN_STRING || state->mode == SCAN_FILE)
		state->source = source;
	return (state->err);
}

t_error	scanner_reset(void)
{
	t_scanner	*scanner;

	scanner = shell_get_scanner();
	if (!scanner)
		return (error(ERR_SHELL_NOT_FOUND));
	lexer_reset(&scanner->lexer);
	return (error(ERR_NO));
}
