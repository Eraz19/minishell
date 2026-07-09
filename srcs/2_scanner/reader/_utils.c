#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "libft.h"
#include "shell.h"
#include "reader_.h"

t_error	readline_(t_string *res, const char *prompt)
{
	t_error	err;
	char	*input;

	if (prompt == NULL)
		prompt = "";
	input = readline(prompt);
	while (input == NULL)
	{
		err = shell_should_exit_on_veof();
		if (err.type)
			return (err);
		input = readline(prompt);
	}
	if (!string_init(res, 0, input, -1))
		return (free(input), error_sys());
	free(input);
	if (!string_append_n(res, "\n", 1))
		return (err = error_sys(), string_free(res), err);
	return (error(ERR_NO));
}

t_error	reader_read_error(const char *source)
{
	t_error	err;

	err = error_print(error_sys(), "scanner", source, NULL, NULL);
	err.type = ERR_POSIX_READ;
	return (err);
}
