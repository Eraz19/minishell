#include "cmd_search_priv.h"
#include "params.h"
#include "utils.h"

t_error	cmd_search_try_cache(
			const t_string *cmd_name,
			t_cmd_entry_point *out_entry_point)
{
	t_cmd_cache		*cmd_cache;
	const t_string	*cmd_path_from_cache;
	bool			found;
	t_error			err;

	err = params_get_cmd_cache(&cmd_cache);
	if (err.type == ERR_NO)
		err = cmd_cache_get(cmd_cache, cmd_name, &cmd_path_from_cache);
	if (err.type)
		return (err);
	found = false;
	err = file_check(cmd_path_from_cache, EXECUTABLE, &found);
	if (err.type == ERR_FILE_NOT_FOUND || err.type == ERR_FILE_NOT_EXECUTABLE)
		cmd_cache_unset(cmd_cache, cmd_name);
	if (err.type)
		return (cmd_convert_file_error(err));
	if (!string_dup(&out_entry_point->data.cmd_path, cmd_path_from_cache))
		return (error_sys());
	out_entry_point->type = CMD_EXTERNAL;
	cmd_search_try_regular_builtin(out_entry_point);
	return (error(ERR_NO));
}
