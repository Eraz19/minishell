#include "alias.h"
#include <stdlib.h>

bool	alias_is_valid_name(const char *name)
{
	size_t	i;

	if (name == NULL || *name == '\0')
		return (false);
	i = 0;
	while (name[i] != '\0')
	{
		if (!ft_isalnum(name[i])
			&& name[i] != '_'
			&& name[i] != '!'
			&& name[i] != '%'
			&& name[i] != ','
			&& name[i] != '-'
			&& name[i] != '@')
			return (false);
		i++;
	}
	return (true);
}

t_error	alias_interpret_operand(const char *operand)
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

t_error	alias_interpret_operands(int argc, char **argv)
{
	int		i;
	t_error	err;

	i = 0;
	while (i < argc)
	{
		err = alias_interpret_operand(argv[i]);
		if (err.type)
			return (err);
		i++;
	}
	return (error(ERR_NO));
}

t_error	builtin_alias(int argc, char **argv, char **envp, int *exit_status)
{
	t_error	err;

	(void)envp;
	if (argc == 1)
		err = alias_print(NULL);
	else
		err = alias_interpret_operands(argc - 1, argv + 1);
	*exit_status = (int)err.type;
	return (err);
}
