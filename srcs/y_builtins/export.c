#include "variable.h"
#include <stdlib.h>

// value can be NULL
t_error	export(t_var_list *variables, const char *name, const char *value)
{
	size_t	var_index;
	t_var	new_var;
	t_var	*current_var;
	t_error	error;

	if (!var_name_is_valid(name))
		return (ERR_VAR_INVALID_NAME);
	if (!var_find(variables, name, &var_index))
	{
		new_var = var_new(name, value, true, false);
		if (!new_var.name || (value && !new_var.value))
			return (var_free(&new_var), ERR_LIBC);
		if (!vector_push(variables, &new_var))
			return (var_free(&new_var), ERR_LIBC);
		return (ERR_NO);
	}
	if (value)
	{
		error = var_set(variables, name, value);
		if (error != ERR_NO)
			return (error);
	}
	current_var = &((t_var *)variables->data)[var_index];
	current_var->export = true;
	return (ERR_NO);
}

t_error	export_print(const t_var_list *variables)
{
	size_t	i;
	t_var	*var;
	t_error	error;

	i = 0;
	while (i < variables->len)
	{
		var = &((t_var *)variables->data)[i++];
		if (!var->export)
			continue ;
		error = var_print("export ", var);
		if (error != ERR_NO)
			return (error);
	}
	return (ERR_NO);
}

static t_error	export_build_entry(
	const char *name,
	const char *value,
	char **dst)
{
	size_t	name_len;
	size_t	value_len;
	size_t	dst_size;

	name_len = str_len(name);
	value_len = 0;
	if (value)
		value_len = str_len(value);
	dst_size = name_len + value_len + 2;
	*dst = malloc(dst_size);
	if (!*dst)
		return (ERR_LIBC);
	str_lcpy(*dst, name, dst_size);
	(*dst)[name_len] = '=';
	if (value_len > 0)
		str_lcpy(*dst + name_len + 1, value, dst_size - name_len - 1);
	else
		(*dst)[name_len + 1] = '\0';
	return (ERR_NO);
}

t_error	export_build_envp(const t_var_list *variables, char ***dst_envp)
{
	size_t	envp_i;
	size_t	var_i;
	t_var	*var;
	t_error	error;

	*dst_envp = malloc((variables->len + 1) * sizeof(**dst_envp));
	if (!*dst_envp)
		return (ERR_LIBC);
	envp_i = 0;
	var_i = 0;
	while (var_i < variables->len)
	{
		var = &((t_var *)variables->data)[var_i++];
		if (!var->export || !var->value)
			continue ;
		error = export_build_entry(var->name, var->value, &(*dst_envp)[envp_i]);
		if (error != ERR_NO)
			return (str_array_free(dst_envp), error);
		envp_i++;
	}
	(*dst_envp)[envp_i] = NULL;
	return (ERR_NO);
}
