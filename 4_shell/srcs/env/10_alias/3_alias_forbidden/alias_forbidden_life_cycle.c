#include "alias_forbidden_internal.h"

void	alias_forbidden_init(t_alias_forbidden *forbidden)
{
	(void)hashmap_init(forbidden, 0, NULL);
}

void	alias_forbidden_clear(t_alias_forbidden *forbidden)
{
	hashmap_clear(forbidden);
}

void	alias_forbidden_free(t_alias_forbidden *forbidden)
{
	hashmap_free(forbidden);
}
