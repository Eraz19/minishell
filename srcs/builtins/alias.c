#include "alias.h"
#include <stdlib.h>

static t_error	alias_interpret_operand(const char *operand)
{
	t_error	err;
	char	*name;
	char	*value;
	size_t	value_len;
	char	*equal_sign;

	equal_sign = str_chr(operand, '=');
	if (equal_sign == NULL)
		err = alias_print(operand);
	else
	{
		name = str_sub(operand, 0, (size_t)(equal_sign - operand));
		if (name == NULL)
			return (error_sys());
		if (!alias_is_valid_name(name))
			return (free(name), error(ERR_ALIAS_INVALID_NAME));
		value_len = str_len(equal_sign + 1);
		value = str_sub(operand, (uint)(equal_sign - operand + 1), value_len);
		if (value == NULL)
			return (err = error_sys(), free(name), err);
		err = alias_add(name, value);
		free(name);
		free(value);
	}
	return (err);
}

static t_error	alias_interpret_operands(int start, int argc, char **argv)
{
	int		i;
	t_error	last_exit_status;
	t_error	exit_status;

	exit_status = error(ERR_NO);
	i = start;
	while (i < argc)
	{
		last_exit_status = alias_interpret_operand(argv[i]);
		if (last_exit_status.type != ERR_NO)
		{
			exit_status = error_print(
					last_exit_status, argv[0], argv[i], NULL, NULL);
		}
		i++;
	}
	return (exit_status);
}

t_error	builtin_alias(int argc, char **argv, char **envp, int *exit_status)
{
	t_error	err;
	int		first_operand;

	(void)envp;
	first_operand = 1;
	if (argc > 1 && str_cmp(argv[1], "--") == 0)
		first_operand = 2;
	if (first_operand >= argc)
		err = alias_print(NULL);
	else
		err = alias_interpret_operands(first_operand, argc, argv);
	*exit_status = (err.type != ERR_NO);
	if (err.type)
		err = error_print(err, argv[0], NULL, NULL);
	if (err.type == ERR_ALIAS_NOT_FOUND
		|| err.type == ERR_ALIAS_INVALID_NAME
		|| err.type == ERR_POSIX_WRITE)
		err.type = ERR_BUILTIN;
	else if (err.type == ERR_SHELL_NOT_FOUND)
		err.type = ERR_INTERNAL;
	return (err);
}
