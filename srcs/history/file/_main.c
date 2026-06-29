#include <fcntl.h>
#include "history_file_.h"
#include "posix_helpers.h"

t_error	history_file_read(t_history_file *state)
{
	int		fd;
	t_buff	content_buff;

	if (history_file_open(state, &fd, O_RDONLY).type)
		return (state->err);
	buff_init(&content_buff, 0, NULL, 0);
	if (!buff_read_all(&content_buff, fd))
		return (state->err = error_sys(), posix_close(fd),
			buff_free(&content_buff), state->err);
	posix_close(fd);
	if (content_buff.len == 0)
		return (buff_free(&content_buff), state->err);
	state->content = buff_get_string(&content_buff);
	if (state->content == NULL)
		return (state->err = error_sys(), buff_free(&content_buff), state->err);
	return (buff_free(&content_buff), state->err);
}

t_error	history_file_write(t_history_file *state)
{
	int	fd;

	if (history_file_open(state, &fd, O_WRONLY | O_APPEND).type)
		return (state->err);
	state->err = posix_write(fd, state->content, str_len(state->content));
	if (state->err.type)
		return (posix_close(fd), state->err);
	return (state->err = posix_close(fd), state->err);
}
