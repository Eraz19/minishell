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

void	var_free(void *var)
{
	t_var	*var_casted;

	var_casted = (t_var *)var;
	if (var_casted->name)
		free(var_casted->name);
	var_casted->name = NULL;
	if (var_casted->value)
		free(var_casted->value);
	var_casted->value = NULL;
	var_casted->export = false;
	var_casted->readonly = false;
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

	printf("-------------------------------------\n");
	printf("===> [var_load_envp]\n");
	error = var_load_envp(variables, envp);
	if (error != ERR_NO)
		return (error);
	printf("===> [var_load_envp]            => (entries: %'6zu)\n", variables->len);
	printf("-------------------------------------\n");
	printf("===> [var_load_mandatory]\n");
	error = var_load_mandatory(variables, parent_shell_ppid);
	if (error != ERR_NO)
		return (error);
	printf("===> [var_load_mandatory]       => (entries: %'6zu)\n", variables->len);
	printf("-------------------------------------\n");
	printf("===> [var_load_up]\n");
	error = var_load_up(variables);
	if (error != ERR_NO)
		return (error);
	printf("===> [var_load_up]              => (entries: %'6zu)\n", variables->len);
	printf("-------------------------------------\n\n");
	return (ERR_NO);
}

void	var_free_all(t_var_list *variables)
{
	vector_free(variables, var_free);
}
