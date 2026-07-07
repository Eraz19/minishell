#ifndef CMD_ERROR_H
# define CMD_ERROR_H

# include "libft.h"
# include "error.h"

// @ret ERR_CMD_NOT_FOUND
t_error	cmd_not_found(const t_string *cmd_name);

// @ret ERR_CMD_NOT_EXECUTABLE
t_error	cmd_not_executable(const t_string *cmd_name);

#endif
