#include "variables.h"
#include "posix_helpers.h"
#include <unistd.h>

// Errors can be ERR_LIBC
static t_error	var_print_escaped_value(const char *value)
{
	t_error	error;
	size_t	i;

	i = 0;
	while (value[i])
	{
		if (value[i] == '\'')
		{
			error = posix_write(STDOUT_FILENO, "'\\''", 4);
			if (error != ERR_NO)
				return (error);
		}
		else
		{
			error = posix_write(STDOUT_FILENO, &value[i], 1);
			if (error != ERR_NO)
				return (error);
		}
		i++;
	}
	return (ERR_NO);
}

t_error	var_print(const char *prefix, const t_var *var)
{
	size_t	len;
	t_error	error;

	len = str_len(prefix);
	error = posix_write(STDOUT_FILENO, prefix, len);
	if (error != ERR_NO)
		return (error);
	len = str_len(var->name);
	error = posix_write(STDOUT_FILENO, var->name, len);
	if (error != ERR_NO)
		return (error);
	if (var->value)
	{
		error = posix_write(STDOUT_FILENO, "='", 2);
		if (error != ERR_NO)
			return (error);
		error = var_print_escaped_value(var->value);
		if (error != ERR_NO)
			return (error);
		error = posix_write(STDOUT_FILENO, "'", 1);
		if (error != ERR_NO)
			return (error);
	}
	return (posix_write(STDOUT_FILENO, "\n", 1));
}
