#include <stdlib.h>
#include "scanner.h"
# include "logs.h"	// DEBUG

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
	print_title("scanner_load()");
	state->mode = mode;
	print_pass("mode set to %i\n", (int)mode);
	lexer_load(&state->lexer, mode == SCAN_STDIN);
	print_pass("lexer_load()\n");
	print_result("scanner_load()");
	if (mode == SCAN_STRING)
		return (state->source = source, state->err);
	else if (mode == SCAN_FILE)
		return (state->source = source, state->err);
	return (state->err);
}
