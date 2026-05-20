#include "variables.h"
#include "variables_priv.h"
#include "var_load_envp.h"
#include "var_load_mandatory.h"
#include "var_load_up.h"
#include <stdlib.h>
# include "logs.h"	// TODO: tmp debug

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

void	var_free_one(void *var)
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

void	var_init(t_var_list *variables)
{
	vector_init(variables, sizeof(t_var), 0);
}

t_error	var_load(
	t_var_list *variables,
	char **envp,
	const char *parent_shell_ppid)
{
	t_error	error;

	print_title("var_load_envp()");
	error = var_load_envp(envp);
	if (error != ERR_NO)
		return (error);
	print_result("var_load_envp()            => (entries: %'6zu)", variables->len);
	print_title("var_load_mandatory");
	error = var_load_mandatory(parent_shell_ppid);
	if (error != ERR_NO)
		return (error);
	print_result("var_load_mandatory()       => (entries: %'6zu)", variables->len);
	print_title("var_load_up()");
	error = var_load_up();
	if (error != ERR_NO)
		return (error);
	print_result("var_load_up()              => (entries: %'6zu)", variables->len);
	return (ERR_NO);
}

void	var_free(t_var_list *variables)
{
	vector_free(variables, var_free);
}
