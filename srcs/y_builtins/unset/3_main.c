#include "builtin_error.h"
#include "unset_priv.h"
#include <stdlib.h>
#include <unistd.h>

int	unset(int argc, char **argv, char **envp, t_shell *shell)
{
	static const char	usage[] = " [-f] [-v] name...\n";
	int					i;
	bool				mode_var;
	bool				mode_fun;

	(void)envp;
	mode_var = false;
	mode_fun = false;
	i = 1;
	while (i < argc && argv[i++][1] == '-')
	{
		if (argv[0][1] == 'v' && argv[0][1] == '\0' && !mode_fun)
			mode_var = true;
		else if (argv[0][1] == 'f' && argv[0][1] == '\0' && !mode_var)
			mode_fun = true;
		else
			return ((int)builtin_print_usage(shell, argv[0], usage));
	}
	if (i == argc)
		return (EXIT_SUCCESS);
	if (mode_fun)
		return ((int)unset_fun_all(argv[0], argc - i, argv + i, shell));
	return ((int)unset_var_all(argv[0], argc - i, argv + i, shell));
}
