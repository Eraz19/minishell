#include "variables.h"
#include "variables_priv.h"
#include "utils.h"
#include <stdlib.h>
# include <assert.h>	// DEBUG

// @ret ERR_LIBC
static inline t_error	var_envp_add_entry(
							const char *name,
							const t_string *value,
							t_vector *dst_envp)
{
	size_t		name_len;
	t_string	entry;
	t_error		err;

	assert(name != NULL);
	assert(value != NULL);
	assert(dst_envp != NULL);
	name_len = str_len(name);
	if (!string_init(&entry, name_len + value->len + 2, name, (long)name_len))
		return (error_sys());
	if (!string_append_n(&entry, "=", 1))
		return (err = error_sys(), string_free(&entry), err);
	if (!string_append_n(&entry, value->data, (long)value->len))
		return (err = error_sys(), string_free(&entry), err);
	if (!vector_push(dst_envp, &entry.data))
		return (err = error_sys(), string_free(&entry), err);
	return (error(ERR_NO));
}

// @ret ERR_LIBC
static inline t_error	var_envp_process_key_value(
							t_vector *dst_envp,
							const t_key_value *key_value)
{
	const char	*name;
	const t_var	*value;

	name = key_value->key;
	value = key_value->value;
	if (value->export == false || value->value.data == NULL)
		return (error(ERR_NO));
	return (var_envp_add_entry(name, &value->value, dst_envp));
}

t_error	var_build_envp(const t_var_list *variables, t_vector *dst_envp)
{
	const t_key_value	**var_list;
	size_t				i;
	t_error				err;

	assert(variables != NULL);
	assert(dst_envp != NULL);
	var_list = hashmap_get_all(variables);
	if (var_list == NULL)
		return (err = error_sys(), err);
	if (!vector_init(dst_envp, sizeof(char *), variables->size + 1))
		return (err = error_sys(), free(var_list), err);
	i = 0;
	while (var_list[i] != NULL)
	{
		err = var_envp_process_key_value(dst_envp, var_list[i]);
		if (err.type)
		{
			free(var_list);
			vector_free(dst_envp, free_char_ptr_void);
			return (err);
		}
		i++;
	}
	free(var_list);
	return (error(ERR_NO));
}
