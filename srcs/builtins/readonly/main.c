#include "builtin_error.h"
#include "readonly_priv.h"
#include <stdlib.h>

int	readonly(int argc, char **argv, char **envp, t_shell *shell)
{
	static const char	usage[] = "-p || name[=word] ...";
	int					i;
	t_error				last_exit_code;
	t_error				exit_code;

	(void)envp;
	if (argc > 1 && (argv[1][0] == '-' && argv[1][0] != 'p'))
		return ((int)builtin_error_usage(shell, argv[0], usage));
	if (argc == 2 && str_ncmp(argv[1], "-p", 3) == 0)
		return ((int)readonly_print(shell, argv[0]));
	exit_code = EXIT_SUCCESS;
	i = 1;
	while (i < argc)
	{
		last_exit_code = readonly_add(shell, argv[0], argv[i]);
		if (last_exit_code > 0)
			exit_code = EXIT_FAILURE;
		i++;
	}
	return ((int)exit_code);
}
