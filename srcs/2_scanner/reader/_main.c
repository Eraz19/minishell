#include "libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "reader_.h"
#include "history.h"

t_error	reader_new_input(char **res)
{
	t_error	err;

	history_save_entry();
	err = readline_(res, "$ ");
	if (err.type)
		return (err);
	if (str_len(*res) == 1)
		return (free(*res), *res = NULL, error(ERR_NO));
	err = history_append_to_entry(*res);
	if (err.type)
		return (free(*res), err);
	return (error(ERR_NO));
}

t_error	reader_continuation(char **res)
{
	t_error	err;
	char	*new_input;
	char	*continuation;

	err = readline_(&continuation, "> ");
	if (err.type)
		return (err);
	err = history_append_to_entry(continuation);
	if (err.type)
		return (free(continuation), err);
	new_input = str_join(*res, continuation);
	if (new_input == NULL)
		return (free(continuation), error_sys());
	return (free(*res), free(continuation), *res = new_input, error(ERR_NO));
}

t_error	reader_file_input(char **res, const char *path)
{
	int		fd;
	t_buff	buffer;
	char	*content;

	fd = open(path, O_RDONLY);	// TODO: use posix_open()
	if (fd < 0)
		return (error(ERR_OPEN_FILE));
	buff_init(&buffer, 0, NULL, 0);
	if (!buff_read_all(&buffer, fd))
		return (close(fd), buff_free(&buffer), error_sys());
	content = buff_get_string(&buffer);
	if (content == NULL)
		return (close(fd), buff_free(&buffer), error_sys());
	*res = str_join(content, "\n");
	if (*res == NULL)
		return (close(fd), buff_free(&buffer), free(content), error_sys());
	return (close(fd), buff_free(&buffer), free(content), error(ERR_NO));
}
