#include "cmd_cache.h"
#include "options.h"

t_error	cmd_cache_get(
			const t_cmd_cache *cache,
			const t_string *cmd_name,
			const t_string **out_cmd_path)
{
	bool	hash_cmds_is_active;
	t_error	err;

	*out_cmd_path = NULL;
	err = option_is_active(OPT_HASH_CMDS, &hash_cmds_is_active);
	if (err.type)
		return (err);
	if (hash_cmds_is_active == false)
		return (error(ERR_NO));
	*out_cmd_path = hashmap_get(cache, cmd_name->data);
	return (error(ERR_NO));
}
