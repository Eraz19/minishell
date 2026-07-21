#include "libft.h"
#include <errno.h>
#include <fcntl.h>
#include "options.h"
#include "reader_.h"
#include "history.h"
#include "posix_helpers.h"

t_error	reader_new_input(t_string *res)
{
	t_error		err;
	t_string	ps1;

	err = history_save_entry();
	if (err.type)
		return (err);
	(void)string_init(res, 0, NULL, 0);
	while (res->len < 2)
	{
		res->len = 0;
		err = reader_build_prompt("PS1", &ps1);
		if (err.type == ERR_NO)
			err = reader_read_next_line(res, ps1.data);
		string_free(&ps1);
		if (err.type)
			return (err);
	}
	err = history_append_to_entry(res);
	if (err.type)
		return (string_free(res), err);
	return (err);
}

t_error	reader_continuation(t_string *res)
{
	t_error		err;
	t_string	ps2;
	t_string	continuation;
	bool		is_interactive;

	err = option_is_active(OPT_INTERACTIVE, &is_interactive);
	if (err.type)
		return (err);
	if (!is_interactive)
		return (error(ERR_POSIX_SYNTAX));
	(void)string_init(&continuation, 0, NULL, 0);
	while (continuation.len < 2)
	{
		continuation.len = 0;
		err = reader_build_prompt("PS2", &ps2);
		if (err.type == ERR_NO)
			err = reader_read_next_line(&continuation, ps2.data);
		string_free(&ps2);
		if (err.type)
			return (string_free(&continuation), err);
	}
	err = history_append_to_entry(&continuation);
	if (err.type)
		return (string_free(&continuation), err);
	if (!string_append(res, &continuation))
		return (err = error_sys(), string_free(&continuation), err);
	return (string_free(&continuation), err);
}

static t_error	reader_open_source(const char *path, int *fd)
{
	t_error	err;

	err = posix_open(path, O_RDONLY, fd);
	if (err.type != ERR_LIBC)
		return (err);
	err = error_print(err, "scanner", path, NULL, NULL);
	if (err.saved_errno == ENOENT)
		err.type = ERR_POSIX_CMD_NOT_FOUND;
	else
		err.type = ERR_POSIX_CMD_NOT_EXECUTABLE;
	return (err);
}

t_error	reader_file_input(t_string *res, const char *path)
{
	int			fd;
	t_error		err;

	err = reader_open_source(path, &fd);
	if (err.type)
		return (err);
	err = posix_read_all(fd, res);
	if (err.type == ERR_LIBC)
	{
		err = reader_read_error(err, path);
		return (error_priorize(err, posix_close_if_open(fd)));
	}
	err = posix_close_if_open(fd);
	if (err.type)
		return (string_free(res), err);
	if (!string_append_n(res, "\n", 1))
		return (err = error_sys(), string_free(res), err);
	return (err);
}
