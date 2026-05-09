#include "shell.h"
#include <stdlib.h>

// Errors: ERR_VAR_INVALID_NAME / ERR_VAR_READ_ONLY / ERR_INDEX_OUT_OF_BOUND
static t_error	unset_var_one(
	const char *builtin,
	t_shell *shell,
	const char *name)
{
	size_t	var_index;
	t_var	*var;

	if (!var_name_is_valid(name))
		return (error_print(builtin, name, ERR_VAR_INVALID_NAME));
	if (!var_find(&shell->variables, name, &var_index))
		return (ERR_NO);
	var = &((t_var *)shell->variables.data)[var_index];
	if (var->readonly)
		return (error_print(builtin, name, ERR_VAR_READ_ONLY));
	var_free(var);
	if (!vector_remove(&shell->variables, var_index, NULL))
		return (error_print(builtin, name, ERR_INDEX_OUT_OF_BOUND));
	return (ERR_NO);
}

t_error	unset_var(const char *builtin, int argc, char **argv, t_shell *shell)
{
	int		i;
	t_error	last_error;
	t_error	exit_code;

	exit_code = EXIT_SUCCESS;
	i = 0;
	while (i < argc)
	{
		last_error = unset_var_one(builtin, shell, argv[i]);
		if (last_error != ERR_NO)
			exit_code = last_error;
		i++;
	}
	return (exit_code);
}
