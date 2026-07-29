#include "builtins.h"
#include "alias.h"
#include <stdlib.h>

static t_error	alias_print_pair(const char *name, const char *value)
{
	t_error		err;
	t_string	line;
	t_string	escaped_value;

	if (value == NULL)
		value = "";
	if (!string_init(&line, 0, name, -1))
		return (error_sys());
	if (!string_append_n(&line, "=", 1))
		return (err = error_sys(), string_free(&line), err);
	err = serialize(value, &escaped_value);
	if (err.type)
		return (string_free(&line), err);
	if (!string_append(&line, &escaped_value))
		return (err = error_sys(), string_free(&escaped_value),
			string_free(&line), err);
	string_free(&escaped_value);
	if (!string_append_n(&line, "\n", 1))
		return (err = error_sys(), string_free(&line), err);
	err = posix_write(STDOUT_FILENO, line.data, line.len);
	return (string_free(&line), err);
}

t_error	alias_print_all(const t_key_value **pairs)
{
	t_error	err;
	size_t	i;

	err = error(ERR_NO);
	if (pairs == NULL)
		return (err);
	i = 0;
	while (pairs[i] != NULL && err.type == ERR_NO)
	{
		err = alias_print_pair(pairs[i]->key, (const char *)pairs[i]->value);
		i++;
	}
	return (free(pairs), err);
}

t_error	alias_print_one(t_alias *alias, const char *name)
{
	const char	*value;

	value = hashmap_get_const(&alias->map, name);
	if (value == NULL)
		return (error(ERR_ALIAS_NOT_FOUND));
	return (alias_print_pair(name, value));
}


t_error	alias_print(const char *name)
{
	t_alias				*alias;
	const t_key_value	**pairs;

	alias = shell_get_alias();
	if (alias == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	if (name != NULL)
		return (alias_print_one(alias, name));
	pairs = hashmap_get_all(&alias->map);
	if (pairs == NULL)
		return (alias->err = error_sys());
	return (alias_print_all(pairs));
}

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
