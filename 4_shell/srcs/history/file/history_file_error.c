#include "history_file_priv.h"

t_error	on_history_file_open_error(t_error err, const char *path)
{
	(void)error_print(err,
		"history",
		"unable to open history file",
		"persistent history disabled", NULL,
		"%s", path);
	return (err.type = ERR_NO, err);
}

t_error	on_history_file_read_error(t_error err, const char *path)
{
	return (error_print(err,
		"history",
		"unable to read history file",
		"persistent history disabled", NULL,
		"%s", path));
}

t_error	on_history_file_write_error(t_error err, const char *path)
{
	(void)error_print(err,
		"history",
		"unable to write to history file",
		"persistent history disabled", NULL,
		"%s", path);
	return (err.type = ERR_NO, err);
}
