#include <fcntl.h>
#include "posix_helpers.h"
#include "history_file_priv.h"

t_error	read_history_file(t_history_file *history_file)
{
	int	fd;

	if (history_file->path.len == 0)
		return (history_file->err);
	history_file->err = open_history_file(&fd, history_file->path.data, O_CREAT | O_RDONLY);
	if (history_file->err.type)
		return (history_file->err);
	history_file->err = posix_read_all(fd, &history_file->content);
	if (history_file->err.type)
	{
		on_history_file_read_error(history_file->err, history_file->path.data);
		string_free(&history_file->content);
	}
	return (history_file->err = posix_close_if_open(fd));
}
