#include "variables_priv.h"
#include <stdlib.h>
# include <assert.h>	// DEBUG

// @ret ERR_LIBC
static inline t_error	var_build_entry(
							const t_string *name,
							const t_string *value,
							char **dst)
{
	size_t	dst_size;

	assert(name != NULL);
	assert(value != NULL);
	assert(dst != NULL);
	dst_size = name->len + value->len + 2;
	*dst = malloc(dst_size);
	if (!*dst)
		return (error_sys());
	str_lcpy(*dst, name->data, dst_size);
	(*dst)[name->len] = '=';
	if (value->len > 0)
		str_lcpy(*dst + name->len + 1, value->data, dst_size - name->len - 1);
	else
		(*dst)[name->len + 1] = '\0';
	return (error(ERR_NO));
}

t_error	var_build_envp(const t_var_list *variables, char ***dst_envp)
{
	size_t		envp_i;
	size_t		var_i;
	const t_var	*var;
	t_error		err;

	assert(variables != NULL);
	assert(dst_envp != NULL);
	*dst_envp = malloc((variables->len + 1) * sizeof(**dst_envp));
	if (!*dst_envp)
		return (error_sys());
	envp_i = 0;
	var_i = 0;
	while (var_i < variables->len)
	{
		var = &((const t_var *)variables->data)[var_i++];
		if (!var->export || !var->value.data)
			continue ;
		err = var_build_entry(&var->name, &var->value, &(*dst_envp)[envp_i]);
		if (err.type)
			return (str_array_free(dst_envp), err);
		envp_i++;
	}
	(*dst_envp)[envp_i] = NULL;
	return (error(ERR_NO));
}
