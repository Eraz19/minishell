#include "shell.h"
#include "variables_priv.h"
#include "posix_helpers.h"
#include <unistd.h>

// @ret ERR_LIBC
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

// @ret ERR_LIBC
static t_error	var_print_one(const char *prefix, const t_var *var)
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

t_error	var_print(t_var_print_mode mode)
{
	t_shell		*shell;
	t_var_list	*list;
	t_var		*var;
	size_t		i;
	t_error		error;

	shell = shell_get();
	if (!shell)
		return (ERR_SHELL_NOT_FOUND);
	list = &shell->params.variables;
	i = 0;
	error = ERR_NO;
	while (i < list->len)
	{
		var = &((t_var *)list->data)[i];
		if (mode == VAR_PRINT_EXPORT && var->export)
			error = var_print_one("export ", var);
		else if (mode == VAR_PRINT_READONLY && var->readonly)
			error = var_print_one("readonly ", var);
		if (error != ERR_NO)
			break ;
		i++;
	}
	return (error);
}
