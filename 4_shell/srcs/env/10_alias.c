#include "env.h"
#include "shell.h"
# include <assert.h>

t_error	env_set_alias(const char *name, const char *value)
{
	t_params	*params;
	
	params = shell_get_params();
	assert(params != NULL);
	return (alias_set(&params->alias, name, value));
}

t_error	env_get_alias(
			const t_string *name,
			const t_string **out_value,
			bool add_to_stack)
{
	t_params	*params;
	
	params = shell_get_params();
	assert(params != NULL);
	return (alias_get(&params->alias, name, out_value, add_to_stack));
}

bool	env_alias_is_forbidden(const t_string *name)
{
	t_params	*params;

	params = shell_get_params();
	assert(params != NULL);
	return (alias_is_forbidden(&params->alias, name->data));
}

void	env_clear_forbidden_aliases(void)
{
	t_params	*params;

	params = shell_get_params();
	assert(params != NULL);
	alias_clear_forbidden(&params->alias);
}

void	env_pop_alias_from_stack(void)
{
	t_params	*params;

	params = shell_get_params();
	assert(params != NULL);
	alias_pop_from_stack(&params->alias);
}

t_error	env_unset_alias(const char *name)
{
	t_params	*params;

	params = shell_get_params();
	assert(params != NULL);
	return (alias_unset(&params->alias, name));
}

void	env_unset_all_alias(void)
{
	t_params	*params;

	params = shell_get_params();
	assert(params != NULL);
	alias_table_clear(&params->alias.table);
}
