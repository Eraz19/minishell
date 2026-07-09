#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "error.h"
#include "alias.h"
#include "alias_.h"
#include "utils.h"
#include "posix_helpers.h"

// @ret ERR_LIBC / ERR_POSIX_WRITE / ERR_INTERRUPTED / ERR_NO
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

	value = hashmap_get(&alias->map, name);
	if (value == NULL)
		return (error(ERR_ALIAS_NOT_FOUND));
	return (alias_print_pair(name, value));
}
