#include "shell.h"
#include "variables_priv.h"
#include "posix_helpers.h"
#include "utils.h"
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>	// DEBUG

static inline bool	var_must_be_printed(const t_var *var, t_var_print_mode mode)
{
	assert(var != NULL);
	if (mode == VAR_PRINT_EXPORT)
		return (var->export);
	if (mode == VAR_PRINT_READONLY)
		return (var->readonly);
	return (true);
}

static inline const char	*var_select_prefix(t_var_print_mode mode)
{
	if (mode == VAR_PRINT_EXPORT)
		return ("export ");
	if (mode == VAR_PRINT_READONLY)
		return ("readonly ");
	return ("");
}

// @ret ERR_POSIX_WRITE / ERR_LIBC
static inline t_error	var_print_one(
							const char *name,
							const t_var *var,
							t_var_print_mode mode)
{
	t_string	output;
	t_string	serialized_value;
	t_error		err;

	assert(name != NULL);
	assert(var != NULL);
	if (!string_init(&output, 0, var_select_prefix(mode), -1))
		return (error_sys());
	if (!string_append_n(&output, name, -1))
		return (err = error_sys(), string_free(&output), err);
	if (var->value.data)
	{
		if (!string_append_n(&output, "=", 1))
			return (err = error_sys(), string_free(&output), err);
		err = serialize(var->value.data, &serialized_value);
		if (err.type)
			return (string_free(&output), err);
		if (!string_append(&output, &serialized_value))
			return (err = error_sys(), string_free(&serialized_value),
				string_free(&output), err);
		string_free(&serialized_value);
	}
	if (!string_append_n(&output, "\n", -1))
		return (err = error_sys(), string_free(&output), err);
	err = posix_write(STDOUT_FILENO, output.data, output.len);
	return (string_free(&output), err);
}

// @ret ERR_POSIX_WRITE / ERR_LIBC
static inline t_error	var_print_iterate(
							const t_key_value **var_list,
							t_var_print_mode mode)
{
	size_t				i;
	const t_key_value	*key_value;
	t_error				err;

	i = 0;
	err = error(ERR_NO);
	while (var_list[i] != NULL && err.type == ERR_NO)
	{
		key_value = var_list[i];
		if (var_must_be_printed(key_value->value, mode))
			err = var_print_one(key_value->key, key_value->value, mode);
		i++;
	}
	free (var_list);
	return (err);
}

t_error	var_print(t_var_print_mode mode)
{
	t_params			*params;
	const t_key_value	**var_list;

	assert(mode == VAR_PRINT_EXPORT || mode == VAR_PRINT_READONLY || mode == VAR_PRINT_SET);
	params = shell_get_params();
	assert(params != NULL);
	var_list = hashmap_get_all(&params->variables);
	if (var_list == NULL)
		return (error_sys());
	return (var_print_iterate(var_list, mode));
}
