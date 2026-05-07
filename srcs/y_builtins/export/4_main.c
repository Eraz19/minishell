#include "builtins.h"
#include "export_priv.h"
#include "usage.h"
#include <stdlib.h>

int	export(int argc, char **argv, char **envp, t_shell *shell)
{
	static const char	usage1[] = " –p";
	static const char	usage2[] = " name[=word] ...";
	int					i;
	int					last_exit_code;
	int					exit_code;

	(void)envp;
	if (argc < 2 || (argv[1][0] == '-' && argv[1][0] != 'p'))
	{
		builtin_print_usage(argv[0], usage1);
		builtin_print_usage(argv[0], usage2);
		return (EXIT_FAILURE);
	}
	if (argc == 2 && str_ncmp(argv[1], "-p", 3))
		return ((int)export_print(&shell->variables));
	exit_code = EXIT_SUCCESS;
	i = 1;
	while (i < argc)
	{
		last_exit_code = (int)export_add(&shell->variables, argv[i]);
		if (last_exit_code > 0)
			exit_code = EXIT_FAILURE;
		i++;
	}
	return (exit_code);
}
