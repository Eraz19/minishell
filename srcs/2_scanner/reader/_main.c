#include "libft.h"
#include "posix_helpers.h"
#include <fcntl.h>
#include <stdlib.h>
#include "reader_.h"
#include "history.h"
#include "posix_helpers.h"
#include "params.h"

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
		err = params_get_from_const("PS1", &ps1);
		if (err.type == ERR_NO)
			err = readline_(res, ps1.data);
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

	(void)string_init(&continuation, 0, NULL, 0);
	while (continuation.len < 2)
	{
		continuation.len = 0;
		err = params_get_from_const("PS2", &ps2);
		if (err.type == ERR_NO)
			err = readline_(&continuation, ps2.data);
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

t_error	reader_file_input(t_string *res, const char *path)
{
	int			fd;
	t_error		err;

	err = posix_open(path, O_RDONLY, &fd);
	if (err.type)
		return (error_print(error_sys(), "reader", "unable to open source file",
			NULL, "%s", path));
	string_init(res, 0, NULL, 0);
	if (!string_read_all(res, fd))
		return (err = error_sys(), posix_close(fd), string_free(res), err);
	err = posix_close(fd);
	if (err.type)
		return (string_free(res), err);
	if (!string_append_n(res, "\n", 1))
		return (err = error_sys(), string_free(res), err);
	return (err);
}
