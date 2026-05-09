#include "shell.h"
#include <stdlib.h>

void	params_init(t_params *params)
{
	var_init_all(&params->variables);
	options_init(&params->options);
	// TODO: init special params
}

static t_error	params_load_var(t_params *params, char **envp)
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
	size_t	options_count;
	
	error = params_load_var(params, envp);
	if (error != ERR_NO)
		return (error);
	error = options_load(&params->options, argc, argv, &options_count);
	if (error != ERR_NO)
		return (error);
	params->positional_params = (argv += options_count);
	params->positional_count = (size_t)(argc -= options_count);
	// TODO: load special params
	return (ERR_NO);
}

void	params_free(t_params *params)
{
	var_free_all(&params->variables);
	options_free(&params->options);
	// TODO: free special params
}
