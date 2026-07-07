#ifndef INPUT_MODE_H
# define INPUT_MODE_H

# include "error.h"

typedef enum e_input_mode
{
	INPUT_MODE_NONE,		/**< Unset / not yet loaded. */
	INPUT_MODE_FILE,		/**< Read the whole input from a file path. */
	INPUT_MODE_STRING,		/**< Read the input from an in-memory command string. */
	INPUT_MODE_STDIN_TTY,	/**< Read input line-by-line from standard input, with a terminal. */
	INPUT_MODE_STDIN_PIPE	/**< Read input line-by-line from standard input. */
}	t_input_mode;

t_error	input_mode_set(t_input_mode *mode);

#endif
