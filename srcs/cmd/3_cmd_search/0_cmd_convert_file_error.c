#include "cmd_search_priv.h"

t_error	cmd_convert_file_error(t_error err)
{
	if (err.type == ERR_FILE_NOT_FOUND)
		err.type = ERR_POSIX_CMD_NOT_FOUND;
	else if (err.type == ERR_FILE_NOT_EXECUTABLE)
		err.type = ERR_POSIX_CMD_NOT_EXECUTABLE;
	return (err);
}
