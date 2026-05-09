#include "variables.h"
#include "var_load_envp.h"
#include "var_load_mandatory.h"
#include "var_load_up.h"
#include <stdlib.h>
# include <stdio.h>	// TODO: tmp debug

t_var	var_new(const char *name, const char *value, bool export, bool ronly)
{
	t_var	res;

	res.name = str_dup(name);
	if (value)
		res.value = str_dup(value);
	else
		res.value = NULL;
	res.export = export;
	res.readonly = ronly;
	return (res);
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

void	var_init_all(t_var_list *variables)
{
	vector_init(variables, sizeof(t_var), 0);
}

t_error	var_load_all(
	t_var_list *variables,
	char **envp,
	const char *parent_shell_ppid)
{
	t_error	error;

	printf("var_load_env: START\n");
	error = var_load_envp(variables, envp);
	if (error != ERR_NO)
		return (error);
	printf("var_load_env: envp parsed                      (entries: %'6zu)\n", variables->len);
	error = var_load_mandatory(variables, parent_shell_ppid);
	if (error != ERR_NO)
		return (error);
	printf("var_load_env: mandatory variables initialized  (entries: %'6zu)\n", variables->len);
	error = var_load_up(variables);
	if (error != ERR_NO)
		return (error);
	printf("var_load_env: up variables initialized         (entries: %'6zu)\n", variables->len);
	printf("var_load_env: DONE\n");
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
