#include "cmd_cache.h"
#include "shell.h"
#include <assert.h>

void	cmd_cache_clear(t_cmd_cache *cache)
{
	hashmap_clear(cache);
}

t_error	cmd_cache_clear_void(void)
{
	t_runner	*runner;

	runner = shell_get_runner();
	assert(runner != NULL);
	cmd_cache_clear(&runner->cmd_cache);
	return (error(ERR_NO));
}
