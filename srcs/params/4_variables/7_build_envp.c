#include "variables_priv.h"
#include <stdlib.h>
# include <assert.h>	// DEBUG

// @ret ERR_LIBC
static inline t_error	var_add_entry(
							const t_string *name,
							const t_string *value,
							t_vector *dst_envp)
{
	t_string	entry;
	t_error		err;

	assert(name != NULL);
	assert(value != NULL);
	assert(dst_envp != NULL);
	if (!string_init(&entry, name->len + value->len + 2,
		name->data, (long)name->len))
		return (error_sys());
	if (!string_append_n(&entry, "=", 1))
		return (err = error_sys(), string_free(&entry), err);
	if (!string_append_n(&entry, value->data, (long)value->len))
		return (err = error_sys(), string_free(&entry), err);
	if (!vector_push(dst_envp, &entry.data))
		return (err = error_sys(), string_free(&entry), err);
	return (error(ERR_NO));
}

t_error	var_build_envp(const t_var_list *variables, t_vector *dst_envp)
{
	size_t		i;
	const t_var	*var;
	t_error		err;

	assert(variables != NULL);
	assert(dst_envp != NULL);
	if (!vector_init(dst_envp, sizeof(char *), variables->len + 1))
		return (error_sys());
	i = 0;
	while (i < variables->len)
	{
		var = &((const t_var *)variables->data)[i++];
		if (!var->export || !var->value.data)
			continue ;
		err = var_add_entry(&var->name, &var->value, dst_envp);
		if (err.type)
			return (vector_free(dst_envp, free), err);
	}
	return (error(ERR_NO));
}
