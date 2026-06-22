#include <fcntl.h>
#include <unistd.h>
#include "history_file_.h"

t_error	history_file_read(t_history_file *state)
{
	int		fd;
	t_buff	content_buff;

	if (history_file_open(state, &fd, O_RDONLY).type)
		return (state->err);
	buff_init(&content_buff, 0, NULL, 0);
	if (!buff_read_all(&content_buff, fd))
		return (buff_free(&content_buff), state->err = error_sys());
	close(fd);
	if (content_buff.len == 0)
		return (buff_free(&content_buff), state->err);
	state->content = buff_get_string(&content_buff);
	if (state->content == NULL)
		return (buff_free(&content_buff), state->err = error_sys());
	return (buff_free(&content_buff), state->err);
}

t_error	history_file_write(t_history_file *state)
{
	int	fd;

	if (history_file_open(state, &fd, O_WRONLY | O_APPEND).type)
		return (state->err);
	if (write(fd, state->content, str_len(state->content)) == -1)
		return (close(fd), state->err = error_sys());
	return (close(fd), state->err);
}
