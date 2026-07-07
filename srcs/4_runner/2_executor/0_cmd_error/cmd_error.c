#include "cmd_error.h"

t_error	cmd_not_found(const t_string *cmd_name)
{
	return (error_print(
				error(ERR_CMD_NOT_FOUND),
				"executor",
				cmd_name->data,
				NULL,
				NULL));
}

t_error	cmd_not_executable(const t_string *cmd_name)
{
	return (error_print(
				error(ERR_CMD_NOT_EXECUTABLE),
				"executor",
				cmd_name->data,
				NULL,
				NULL));
}
