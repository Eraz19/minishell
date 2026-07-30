#ifndef CMD_PRIV_H
# define CMD_PRIV_H

#include "cmd.h"

// @ret ERR_POSIX_CMD_NOT_FOUND / ERR_POSIX_CMD_NOT_EXECUTABLE / ERR_LIBC
t_error	cmd_search(t_cmd *cmd, bool path_is_temporary);

#endif
