#include "shell.h"
#include "variables_priv.h"
#include "posix_helpers.h"
#include "utils.h"
#include <unistd.h>
#include <stdlib.h>
# include <assert.h>	// DEBUG

// @ret ERR_INTERRUPTED / ERR_LIBC
static inline t_error	var_print_one(const char *prefix, const t_var *var)
{
	t_error		err;
	t_string	string;
	t_string	escaped_value;

	assert(prefix != NULL);
	assert(var != NULL);
	if (!string_init(&string, 0, prefix, -1))
		return (error_sys());
	if (!string_append(&string, &var->name))
		return (err = error_sys(), string_free(&string), err);
	if (var->value.data)
	{
		if (!string_append_n(&string, "=", -1))
			return (err = error_sys(), string_free(&string), err);
		err = serialize(var->value.data, &escaped_value);
		if (err.type != ERR_NO)
			return (string_free(&string), err);
		if (!string_append(&string, &escaped_value))
			return (err = error_sys(), string_free(&escaped_value),
				string_free(&string), err);
		string_free(&escaped_value);
	}
	if (!string_append_n(&string, "\n", -1))
		return (err = error_sys(), string_free(&string), err);
	err = posix_write(STDOUT_FILENO, string.data, string.len);
	return (string_free(&string), err);
}

static inline bool	var_print_selects(t_var_print_mode mode, const t_var *var)
{
	if (mode == VAR_PRINT_EXPORT)
		return (var->export);
	if (mode == VAR_PRINT_READONLY)
		return (var->readonly);
	return (true);
}

static inline const char	*var_print_prefix(t_var_print_mode mode)
{
	if (mode == VAR_PRINT_EXPORT)
		return ("export ");
	if (mode == VAR_PRINT_READONLY)
		return ("readonly ");
	return ("");
}

t_error	var_print(t_var_print_mode mode)
{
	t_params	*params;
	t_var_list	*list;
	t_var		*var;
	size_t		i;
	t_error		err;

	assert(mode == VAR_PRINT_EXPORT || mode == VAR_PRINT_READONLY
		|| mode == VAR_PRINT_SET);
	params = shell_get_params();
	if (!params)
		return (error(ERR_SHELL_NOT_FOUND));
	list = &params->variables;
	i = 0;
	err = error(ERR_NO);
	while (i < list->len)
	{
		var = &((t_var *)list->data)[i];
		if (var_print_selects(mode, var))
			err = var_print_one(var_print_prefix(mode), var);
		if (err.type != ERR_NO)
			break ;
		i++;
	}
	return (err);
}
