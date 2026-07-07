#include "libft.h"
#include "error.h"
#include "cmd_searcher_priv.h"

t_error	cmd_try_absolute_path(const t_string *cmd_name, t_string *ref_cmd_path)
{
	if (string_get_index_c(cmd_name, '/') < 0)
		return (error(ERR_CMD_NOT_FOUND));
	if (!string_dup(ref_cmd_path, cmd_name))
		return (error_sys());
	return (error(ERR_NO));
}
