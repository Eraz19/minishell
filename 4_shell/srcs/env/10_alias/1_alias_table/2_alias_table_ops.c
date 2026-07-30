#include "alias_table_internal.h"
#include "alias_table_priv.h"
#include <stdlib.h>

t_error	alias_table_set(
			t_alias_table *table,
			const char *name,
			const char *value)
{
	t_string	*new;
	t_error		err;

	new = malloc(sizeof(*new));
	if (new == NULL)
		return (error_sys());
	if (!string_init(new, 0, value, -1))
		return (err = error_sys(), free(new), err);
	if (!hashmap_put(table, name, new))
		return (err = error_sys(), alias_free_value(new), err);
	return (error(ERR_NO));
}

t_error	alias_table_get(
			const t_alias_table *table,
			const char *name,
			const t_string **out_value)
{
	*out_value = hashmap_get_const(table, name);
	if (out_value == NULL)
		return (error(ERR_VAR_NOT_FOUND));
	return (error(ERR_NO));
}

t_error	alias_table_remove(t_alias_table *table, const char *name)
{
	if (!hashmap_remove(table, name))
		return (error(ERR_VAR_NOT_FOUND));
	return (error(ERR_NO));
}
