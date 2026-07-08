#include "options.h"
#include "input_mode.h"

static inline t_error	scan_compute_options(
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

t_error	input_mode_set(t_input_mode *mode)
{
	t_error	err;
	bool	is_stdin;
	bool	is_interactive;
	bool	is_cmd_string;

	err = scan_compute_options(&is_stdin, &is_interactive, &is_cmd_string);
	if (err.type != ERR_NO)	
		return (err);
	if (is_stdin && is_interactive)
		*mode = INPUT_MODE_STDIN_TTY;
	else if (is_stdin)
		*mode = INPUT_MODE_STDIN_PIPE;
	else if (is_cmd_string)
		*mode = INPUT_MODE_STRING;
	else
		*mode = INPUT_MODE_FILE;
	return (error(ERR_NO));
}
