#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "libft.h"
#include "shell.h"
#include "reader_.h"

t_error	readline_(char **res, const char *prompt)
{
	t_error	err;
	char	*input;

	*res = readline(prompt);
	while (*res == NULL)
	{
		shell_exit_on_veof();
		if (!option_is_active(OPT_INTERACTIVE))
			return (error(ERR_VEOF));
		*res = readline(prompt);
	}
	if (**res == '\0')
	{
		free(*res);
		*res = str_dup("");
		if (*res == NULL)
			return (error_sys());
	}
	input = str_join(*res, "\n");
	if (input == NULL)
		return (err = error_sys(), free(*res), err);
	return (free(*res), *res = input, error(ERR_NO));
}
