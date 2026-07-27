#include "cmd_cache.h"

void	cmd_cache_unset(t_cmd_cache *cache, const t_string *cmd_name)
{
	(void)hashmap_remove(cache, cmd_name->data);
}
