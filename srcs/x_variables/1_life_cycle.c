#include "variable_priv.h"
#include <stdlib.h>
# include <stdio.h>	// TODO: tmp debug

t_var	var_new(const char *name, const char *value, bool export, bool ronly)
{
	return ((t_var)
	{
		.name = str_dup(name),
		.value = str_dup(value),
		.export = export,
		.readonly = ronly
	});
}

void	var_free(t_var *var)
{
	if (var->name)
		free(var->name);
	var->name = NULL;
	if (var->value)
		free(var->value);
	var->value = NULL;
	var->export = false;
	var->readonly = false;
}

void	var_init(t_var_list *variables)
{
	vector_init(variables, sizeof(t_var), 0);
}

t_error	var_load_env(t_var_list *variables, const char **envp)
{
	size_t	i;
	char	*name;
	char	*value;
	t_error	error;

	printf("var_load_env: START\n");
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
		else if (error == ERR_INVALID_POINTER || error == ERR_OUT_OF_MEMORY)
			return (error);
		i++;
	}
	printf("var_load_env: DONE                             (entries: %'6zu)\n", variables->len);
	return (ERR_NO);
}

void	var_free_all(t_var_list *variables)
{
	size_t	i;

	i = 0;
	while (i < variables->len)
	{
		var_free(&((t_var *)variables->data)[i]);
		i++;
	}
	vector_free(variables);
}
