#include "variables.h"
#include "variables_priv.h"
#include "var_load_envp.h"
#include "var_load_mandatory.h"
#include "var_load_up.h"
#include <stdlib.h>
# include "logs.h"		// DEBUG
# include <assert.h>	// DEBUG

void	var_free_one(void *var)
{
	t_var	*var_casted;

	assert(var != NULL);
	var_casted = (t_var *)var;
	string_free(&var_casted->value);
	var_casted->export = false;
	var_casted->readonly = false;
	free(var);
}

void	var_init(t_var_list *variables)
{
	assert(variables != NULL);
	(void)hashmap_init(variables, 0, var_free_one);
}

t_error	var_load(t_var_list *variables, char **envp)
{
	t_error	err;

	assert(variables != NULL);
	assert(envp != NULL);
	print_title("%s()", __func__);
	err = var_load_envp(envp);
	if (err.type != ERR_NO)
		return (err);
	err = var_load_mandatory();
	if (err.type != ERR_NO)
		return (err);
	err = var_load_up();
	if (err.type != ERR_NO)
		return (err);
	print_result("%s()", __func__);
	return (error(ERR_NO));
}

void	var_clear(t_var_list *variables)
{
	assert(variables != NULL);
	hashmap_clear(variables);
}

void	var_free(t_var_list *variables)
{
	assert(variables != NULL);
	hashmap_free(variables);
}
