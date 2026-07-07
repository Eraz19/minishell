#include "libft.h"
#include "error.h"
#include "cmd_searcher_priv.h"

t_error	cmd_try_cache(
			const t_string *cmd_name,
			t_cmd_cache *cache,
			bool *out_found_but_not_executable,
			t_string *ref_cmd_path)
{
	const t_string	*cmd_path_from_cache;
	bool			is_valid;
	t_error			err;

	*out_found_but_not_executable = false;
	if (cache == NULL)
		return (error(ERR_CMD_NOT_FOUND));
	err = cmd_cache_get(cache, cmd_name, &cmd_path_from_cache);
	if (err.type)
		return (err);
	err = cmd_check(cmd_path_from_cache, &is_valid, out_found_but_not_executable);
	if (err.type)
		return (err);
	if (is_valid == false)
		cmd_cache_unset(cache, cmd_name);
	if (*out_found_but_not_executable == true)
		return (error(ERR_CMD_NOT_EXECUTABLE));
	else if (is_valid == false)
		return (error(ERR_CMD_NOT_FOUND));
	if (!string_dup(ref_cmd_path, cmd_path_from_cache))
		return (error_sys());
	return (err);
}
