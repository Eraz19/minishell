#include "posix_helpers.h"
#include "variable.h"
#include <stdlib.h>
#include <unistd.h>

/* ---------- TODO: make it a builtin general public helper ---------- */

void	builtin_print_usage(const char *name, const char *usage)
{
	static const char	prefix[] = ": usage: ";

	(void)posix_write(STDERR_FILENO, name, str_len(name));
	(void)posix_write(STDERR_FILENO, prefix, str_len(prefix));
	(void)posix_write(STDERR_FILENO, name, str_len(name));
	(void)posix_write(STDERR_FILENO, usage, str_len(usage));
}

/* ------------------------------------------------------------------- */

// TODO: add type to functions argument
static int	unset_fun(void *functions, const char *name)
{
	// TODO
	(void)functions;
	(void)name;
	return (ERR_NO);
}

static int	unset_var(size_t argc, const char **argv, t_var_list *variables)
{
	static const char	readonly[] = ": unable to unset readonly variable";
	size_t	i;
	size_t	var_index;
	t_var	*var;
	int		exit_code;

	exit_code = EXIT_SUCCESS;
	i = 0;
	while (i < argc)
	{
		if (!var_find(variables, argv[i++], &var_index))
			continue ;
		var = &((t_var *)variables->data)[var_index];
		if (var->readonly)
		{
			(void)posix_write(STDERR_FILENO, var->name, str_len(var->name));
			(void)posix_write(STDERR_FILENO, readonly, str_len(readonly));
			exit_code = ERR_VAR_READ_ONLY;
			continue ;
		}
		var_free(var);
		if (!vector_remove(variables, var_index, NULL))
			return (ERR_INDEX_OUT_OF_BOUND);
	}
	return (exit_code);
}

int	unset(int argc, char **argv, char **envp, t_shell *shell)
{
	static const char	usage[] = " [-fv] name...\n";

	(void)envp;
	if (argc < 2)
		return (builtin_print_usage(argv[0], usage), EXIT_FAILURE);
	if (argv[1][0] == '-')
	{
		// TODO: allow '-fv'
		// TODO: must contain at least one name (even if there is one or two flags)
		if (argv[1][1] == 'v' && argv[1][2] == '\0')
			return (unset_var(argc - 2, argv + 2, shell->variables));
		if (argv[1][1] == 'f' && argv[1][2] == '\0')
			return (unset_fun(argc - 2, argv + 2, shell->functions));
		return (builtin_print_usage(argv[0], usage), EXIT_FAILURE);
	}
	return (unset_var(argc - 1, argv + 1, shell->variables));
}
