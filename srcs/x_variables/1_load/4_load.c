#include "variable_priv.h"
#include <stdlib.h>
#include <unistd.h>
# include <stdio.h>	// TODO: tmp debug

/*
1. Load envp variables with valid shell names
	- exported = true
	- readonly = false
	- invalid names: do not initialize shell variables from them
*/
static t_error	var_parse_envp(t_var_list *variables, const char **envp)
{
	size_t	i;
	char	*name;
	char	*value;
	t_error	error;

	if (!envp)
		return (ERR_NO);
	i = 0;
	while (envp[i])
	{
		error = var_split(envp[i], &name, &value);
		if (error == ERR_NO && var_name_is_valid(name))
		{
			error = var_set(variables, name, value);
			if (error != ERR_NO)
				return (error);
			error = var_set_export(variables, name, true);
			if (error != ERR_NO)
				return (error);
			printf("+ '%s' = '%s']\n", name, value);
		}
		else if (error == ERR_INVALID_POINTER || error == ERR_LIBC)
			return (error);
		i++;
	}
	return (ERR_NO);
}

/*
2. Initialize mandatory variables
	- IFS = <space><tab><newline>
	- PWD = current working directory (from env or self initialized)
	- PPID = parent process id
*/
static t_error	var_init_mandatory(t_var_list *variables)
{
	t_error	error;

	error = var_set_ifs(variables);
	if (error != ERR_NO)
		return (error);
	error = var_set_pwd(variables);
	if (error != ERR_NO)
		return (error);
	return (var_set_ppid(variables));
}

static t_error	var_init_target_up(t_var_list *variables, const char *name, const char *value)
{
	t_error	error;
	char	*current_value;

	error = var_get(variables, name, &current_value);
	if (error == ERR_NO)
		return (ERR_NO);
	if (error == ERR_VAR_NOT_FOUND)
		error = var_set(variables, name, value);
	if (error == ERR_NO)
		printf("-> '%s' has been set to '%s'\n", name, value);
	return (error);
}

/*
3. Initialize [UP] defaults if you support User Portability Utilities
	- PS1 = "$ " if absent
	- PS2 = "> " if absent
	- PS4 = "+ " if absent
*/
static t_error	var_init_up(t_var_list *variables)
{
	t_error	error;

	error = var_init_target_up(variables, "PS1", "$ ");
	if (error != ERR_NO)
		return (error);
	error = var_init_target_up(variables, "PS2", "> ");
	if (error != ERR_NO)
		return (error);
	return (var_init_target_up(variables, "PS4", "+ "));
}

t_error	var_load(t_var_list *variables, const char **envp)
{
	t_error	error;

	printf("var_load_env: START\n");
	error = var_parse_envp(variables, envp);
	if (error != ERR_NO)
		return (error);
	printf("var_load_env: envp parsed                      (entries: %'6zu)\n", variables->len);
	error = var_init_mandatory(variables);
	if (error != ERR_NO)
		return (error);
	printf("var_load_env: mandatory variables initialized  (entries: %'6zu)\n", variables->len);
	error = var_init_up(variables);
	if (error != ERR_NO)
		return (error);
	printf("var_load_env: up variables initialized         (entries: %'6zu)\n", variables->len);
	printf("var_load_env: DONE\n");
	return (ERR_NO);
}
