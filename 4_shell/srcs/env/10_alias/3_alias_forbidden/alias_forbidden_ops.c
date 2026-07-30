#include "alias_forbidden_internal.h"
# include <assert.h>

t_error	alias_forbidden_set(t_alias_forbidden *forbidden, const char *name)
{
	if (!hashmap_put(forbidden, name, NULL))
		return (error_sys());
	return (error(ERR_NO));
}

bool	alias_forbidden_contains(
			const t_alias_forbidden *forbidden,
			const char *name)
{
	return (hashmap_contains(forbidden, name));
}
