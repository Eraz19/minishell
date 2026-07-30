#include "alias.h"
#include "utils.h"
#include "posix_helpers.h"
#include <unistd.h>
#include <stdlib.h>

static inline t_error	alias_print_one_priv(
							const char *name,
							const t_string *value)
{
	t_string	serialized;
	t_string	formatted;
	t_error		err;

	if (!string_init(&formatted, 0, name, -1))
		return (error_sys());
	if (!string_append_n(&formatted, "=", 1))
		return (err = error_sys(), string_free(&formatted), err);
	err = serialize(value->data, &serialized);
	if (err.type)
		return (string_free(&formatted), err);
	if (!string_append(&formatted, &serialized))
	{
		err = error_sys();
		string_free(&formatted);
		string_free(&serialized);
		return (err);
	}
	string_free(&serialized);
	if (!string_append_n(&formatted, "\n", 1))
		return (err = error_sys(), string_free(&formatted), err);
	err = posix_write(STDOUT_FILENO, formatted.data, formatted.len);
	string_free(&formatted);
	return (err);
}

t_error	alias_print_one(t_alias *alias, const char *name)
{
	const t_string	*value;
	t_error			err;

	err = alias_table_get(&alias->table, name, &value);
	if (err.type)
		return (err);
	return (alias_print_one_priv(name, value));
}

t_error	alias_print_all(t_alias *alias)
{
	const t_key_value	**list;
	size_t				i;
	t_error				err;

	list = hashmap_get_all(&alias->table);
	if (list == NULL)
		return (error_sys());
	i = 0;
	while (list[i] != NULL)
	{
		err = alias_print_one_priv(list[i]->key, list[i]->value);
		if (err.type)
			return (free(list), err);
		i++;
	}
	return (err);
}
