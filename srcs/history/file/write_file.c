#include <fcntl.h>
#include "posix_helpers.h"
#include "history_file_priv.h"

t_error	write_history_file(t_history_file *history_file)
{
	int	fd;

	history_file_save_start_log(history_file);
	if (history_file->path.len == 0 || history_file->content.len == 0)
		return (history_file->err);
	history_file->err = open_history_file(&fd, history_file->path.data, O_CREAT | O_WRONLY | O_APPEND);
	if (history_file->err.type)
		return (history_file->err);
	history_file->err = posix_write(fd, history_file->content.data, history_file->content.len);
	if (history_file->err.type)
		on_history_file_write_error(history_file->err, history_file->path.data);
	history_file_save_end_log(history_file);
	return (history_file->err = posix_close_if_open(fd));
}
