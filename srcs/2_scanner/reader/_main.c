#include "libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include "reader_.h"
#include "history.h"
#include "posix_helpers.h"

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
		return (err = error_sys(), free(continuation), err);
	return (free(*res), free(continuation), *res = new_input, error(ERR_NO));
}

t_error	reader_file_input(char **res, const char *path)
{
	int		fd;
	t_error	err;
	t_buff	buffer;
	char	*content;

	err = posix_open(path, O_RDONLY, &fd);
	if (err.type)
		return (err);
	buff_init(&buffer, 0, NULL, 0);
	if (!buff_read_all(&buffer, fd))
		return (err = error_sys(), posix_close(fd), buff_free(&buffer), err);
	content = buff_get_string(&buffer);
	if (content == NULL)
		return (err = error_sys(), posix_close(fd), buff_free(&buffer), err);
	*res = str_join(content, "\n");
	if (*res == NULL)
	{
		err = error_sys();
		return (posix_close(fd), buff_free(&buffer), free(content), err);
	}
	return (posix_close(fd), buff_free(&buffer), free(content), error(ERR_NO));
}
