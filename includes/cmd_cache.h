#ifndef CMD_CACHE_H
# define CMD_CACHE_H

# include "libft.h"
# include "error.h"

typedef t_hashmap	t_cmd_cache;

void	cmd_cache_init(t_cmd_cache *cache);
t_error	cmd_cache_set(
			t_cmd_cache *cache,
			const t_string *cmd_name,
			t_string *cmd_path);
t_error	cmd_cache_get(
			const t_cmd_cache *cache,
			const t_string *cmd_name,
			const t_string **out_cmd_path);
void	cmd_cache_unset(t_cmd_cache *cache, const t_string *cmd_name);
void	cmd_cache_clear(t_cmd_cache *cache);
void	cmd_cache_free(t_cmd_cache *cache);

#endif
