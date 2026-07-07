#include "cmd_cache.h"
#include <stdlib.h>

static void	cmd_cache_free_value(void *value)
{
	string_free(value);
	free(value);
}

void	cmd_cache_init(t_cmd_cache *cache)
{
	(void)hashmap_init(cache, 0, cmd_cache_free_value);
}

void	cmd_cache_free(t_cmd_cache *cache)
{
	hashmap_free(cache);
}
