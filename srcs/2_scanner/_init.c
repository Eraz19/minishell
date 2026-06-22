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

t_error	scanner_load(t_scanner *state, t_scanner_mode mode, const char *source)
{
	state->mode = mode;
	lexer_load(&state->lexer, mode == SCAN_STDIN);
	if (mode == SCAN_STRING)
		return (state->source = source, state->err);
	else if (mode == SCAN_FILE)
		return (state->source = source, state->err);
	return (state->err);
}
