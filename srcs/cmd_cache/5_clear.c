#include "cmd_cache.h"
#include "shell.h"

void	cmd_cache_clear(t_cmd_cache *cache)
{
	hashmap_clear(cache);
}

t_error	cmd_cache_clear_void(void)
{
	t_runner	*runner;

	runner = shell_get_runner();
	if (runner == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	cmd_cache_clear(&runner->cmd_cache);
	return (error(ERR_NO));
}
