#include "cmd_cache.h"

void	cmd_cache_clear(t_cmd_cache *cache)
{
	hashmap_clear(cache);
}
