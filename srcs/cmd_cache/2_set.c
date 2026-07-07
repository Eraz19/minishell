#include "cmd_cache.h"
#include "options.h"
#include <stdlib.h>

t_error	cmd_cache_set(
			t_cmd_cache *cache,
			const t_string *cmd_name,
			t_string *cmd_path)
{
	bool		hash_cmds_is_active;
	t_string	*allocd_string;
	t_error		err;

	err = option_is_active(OPT_CMD_HASH, &hash_cmds_is_active);
	if (err.type)
		return (err);
	if (hash_cmds_is_active == false)
		return (error(ERR_CMD_HASH_DISABLED));
	allocd_string = malloc(sizeof(*allocd_string));
	if (allocd_string == NULL)
		return (error_sys());
	*allocd_string = *cmd_path;
	if (!hashmap_put(cache, cmd_name->data, allocd_string))
	{
		err = error_sys();
		free(allocd_string);
		return (err);
	}
	(void)string_init(cmd_path, 0, NULL, 0);
	return (error(ERR_NO));
}
