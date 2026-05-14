#include "shell.h"
#include <stdlib.h>

void	params_init(t_params *params)
{
	var_init_all(&params->variables);
	options_init(&params->options);
	specials_init(&params->specials);
}

static t_error	params_load_variables(t_params *params, char **envp)
{
	t_shell	*parent;
	char	*parent_ppid;
	t_error	error;

	parent = (t_shell *)params->parent_shell;
	parent_ppid = NULL;
	if (parent)
	{
		error = var_get(&parent->params.variables, "PPID", &parent_ppid);
		if (error != ERR_NO)
		{
			error_print(NULL, "unable to get PPID from parent shell", error);
			return (error);
		}
	}
	error = var_load_all(&params->variables, envp, parent_ppid);
	if (parent)
		free(parent_ppid);
	return (error);
}

t_error	params_load(t_params *params, int argc, char **argv, char **envp)
{
	t_error	error;
	size_t	start_index;
	
	params->name = argv[0];
	error = params_load_variables(params, envp);
	if (error != ERR_NO)
		return (error);
	start_index = 1;
	error = options_load(&params->options, argc, argv, &start_index);
	if (error != ERR_NO)
		return (error);
	error = specials_load(&params->specials, argc, argv, &start_index);
	if (error != ERR_NO)
		return (error);
	return (positionals_load(&params->positionals, argc, argv, start_index));
}

void	params_free(t_params *params)
{
	if (params->parent_shell)
	{
		shell_free(params->parent_shell);
		free(params->parent_shell);
	}
	var_free_all(&params->variables);
	options_free(&params->options);
	specials_free(&params->specials);
}
