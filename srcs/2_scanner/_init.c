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

static inline t_error	scanner_compute_options(
	bool *is_stdin,
	bool *is_interactive,
	bool *is_cmd_string)
{
	t_error	err;

	err = option_is_active(OPT_STDIN_INPUT, is_stdin);
	if (err.type == ERR_NO)
		err = option_is_active(OPT_INTERACTIVE, is_interactive);
	if (err.type == ERR_NO)
		err = option_is_active(OPT_CMD_STRING, is_cmd_string);
	return (err);
}

t_error	scanner_load(t_scanner *state, const char *source)
{
	bool	is_stdin;
	bool	is_interactive;
	bool	is_cmd_string;
	t_error	err;

	state->mode = SCAN_NONE;
	err = scanner_compute_options(&is_stdin, &is_interactive, &is_cmd_string);
	if (err.type)
		return (err);
	if (is_stdin && is_interactive)
		state->mode = SCAN_STDIN_TTY;
	else if (is_stdin)
		state->mode = SCAN_STDIN_PIPE;
	else if (is_cmd_string)
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
