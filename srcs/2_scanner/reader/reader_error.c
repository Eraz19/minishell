#include "params.h"
#include "reader_priv.h"

t_error	on_read_error(t_error err, const char *path)
{
	err = error_print(err, "scanner", path, "Unrecoverable read error", NULL, NULL);
	err.type = ERR_POSIX_READ;
	return (err);
}

t_error	on_open_error(t_error err, const char *path)
{
	if (err.type && err.type != ERR_LIBC)
		err = error_print(err, "scanner", path, NULL, NULL);
	if (err.type == ERR_FILE_NOT_FOUND)
		err.type = ERR_POSIX_CMD_NOT_FOUND;
	else if (err.type == ERR_FILE_NOT_READABLE)
		err.type = ERR_POSIX_CMD_NOT_EXECUTABLE;
	if (err.type)
		params_set_last_status((int)err.type);
	return (err);
}
