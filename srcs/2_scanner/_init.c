#include "options.h"
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
	state->mode = SCAN_NONE;
	if (option_is_active(OPT_STDIN_INPUT))
	{
		if (option_is_active(OPT_INTERACTIVE))
		{
			state->mode = SCAN_STDIN_TTY;
		}
		else
			state->mode = SCAN_STDIN_PIPE;
	}
	else if (option_is_active(OPT_CMD_STRING))
	{
		state->mode = SCAN_STRING;
		state->source = source;
	}
	else
	{
		state->mode = SCAN_FILE;
		state->source = source;
	}
	return (lexer_load(&state->lexer, (t_lexer_mode)state->mode), state->err);
}

t_error	scanner_reset(t_scanner *state)
{
	lexer_reset(&state->lexer);
	return (error(ERR_NO));
}
