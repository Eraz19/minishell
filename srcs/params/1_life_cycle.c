#include "shell.h"
#include <stdlib.h>

void	params_init(t_params *params)
{
	params->parent_shell = NULL;
	params->name = NULL;
	var_init_all(&params->variables);
	options_init(&params->options);
	specials_init(&params->specials);
	positionals_init(&params->positionals);
}

void	params_free(t_params *params)
{
	if (params->parent_shell)
	{
		shell_free(params->parent_shell);
		free(params->parent_shell);
		params->parent_shell = NULL;
	}
	params->name = NULL;
	var_free_all(&params->variables);
	options_free(&params->options);
	specials_free(&params->specials);
	positionals_free(&params->positionals);
}
