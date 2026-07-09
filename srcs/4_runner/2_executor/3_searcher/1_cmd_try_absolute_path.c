#include "libft.h"
#include "error.h"
#include "cmd_searcher_priv.h"

t_error	cmd_try_absolute_path(t_cmd *cmd)
{
	if (string_get_index_c(&cmd->name, '/') < 0)
		return (error(ERR_POSIX_CMD_NOT_FOUND));
	if (!string_dup(&cmd->path, &cmd->name))
		return (error_sys());
	return (error(ERR_NO));
}
