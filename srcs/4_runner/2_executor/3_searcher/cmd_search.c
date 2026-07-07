#include "cmd_searcher.h"
#include "cmd_searcher_priv.h"
#include "cmd_cache.h"

t_error	cmd_search(
			const t_string *cmd_name,
			const t_vector *envp,
			t_cmd_cache *cache,
			t_string *out_cmd_path)
{
	bool	found;
	t_error	err;

	(void)string_init(out_cmd_path, 0, NULL, 0);
	found = false;
	err = cmd_try_absolute_path(cmd_name, out_cmd_path);
	if (err.type == ERR_CMD_NOT_FOUND)
		err = cmd_try_cache(cmd_name, cache, &found, out_cmd_path);
	if (err.type == ERR_CMD_NOT_FOUND || err.type == ERR_CMD_NOT_EXECUTABLE)
	{
		err = cmd_try_envp_path(cmd_name, cache, envp, out_cmd_path);
		if (err.type == ERR_CMD_NOT_FOUND && found == true)
			err = error(ERR_CMD_NOT_EXECUTABLE);
	}
	if (err.type == ERR_CMD_NOT_FOUND || err.type == ERR_CMD_NOT_EXECUTABLE)
		err = error_print(err, "runner", NULL, "%s", cmd_name->data);
	return (err);
}
