#include "builtins.h"
#include <stdlib.h>
#include <unistd.h>

static t_error	unset_fun(const char *builtin, t_shell *shell, const char *name)
{
	(void)builtin;
	(void)shell;
	(void)name;
	// TODO
	return (ERR_NO);
}

t_error	unset_fun_all(const char *builtin, int argc, char **argv, t_shell *shell)
{
	int		i;
	t_error	last_error;
	t_error	exit_code;

	exit_code = EXIT_SUCCESS;
	i = 0;
	while (i < argc)
	{
		last_error = unset_fun(builtin, shell, argv[i]);
		if (last_error != ERR_NO)
			exit_code = last_error;
		i++;
	}
	return (exit_code);
}
