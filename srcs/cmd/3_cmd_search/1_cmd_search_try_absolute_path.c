#include "cmd_search_priv.h"

t_error	cmd_search_try_absolute_path(
			const t_string *cmd_name,
			t_cmd_entry_point *out_entry_point)
{
	if (string_get_index_c(cmd_name, '/') < 0)
		return (error(ERR_POSIX_CMD_NOT_FOUND));
	if (!string_dup(&out_entry_point->data.cmd_path, cmd_name))
		return (error_sys());
	out_entry_point->type = CMD_EXTERNAL;
	return (error(ERR_NO));
}
