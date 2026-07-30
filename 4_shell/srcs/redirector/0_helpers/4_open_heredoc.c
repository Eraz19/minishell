#include "redirector_priv.h"
#include "fd.h"
#include "posix_helpers.h"
#include <limits.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

static inline t_error	redirect_print_and_qualify(
							t_error err,
							bool requalify_libc_errors,
							const char *message)
{
	if (err.type == ERR_NO || err.type == ERR_INTERRUPTED)
		return (err);
	err = error_print(err,
			message, NULL, NULL);
	if (err.type == ERR_INTERNAL || err.type == ERR_INVALID_USAGE)
		return (err);
	if (requalify_libc_errors == true && err.type == ERR_LIBC)
		err.type = ERR_REDIRECTION;
	return (err);
}

t_error	redirect_prepare_heredoc_file(const t_string *body, char **out_path)
{
	int			fd;
	t_string	path;
	t_error		err;
	t_error		close_err;

	err = fd_open_heredoc(&path, &fd);
	if (err.type)
		return (redirect_print_and_qualify(err, false,
					"unable to create heredoc file"));
	err = posix_write(fd, body->data, body->len);
	if (err.type)
		err = redirect_print_and_qualify(err, true,
					"unable to write to heredoc file");
	close_err = posix_close_if_open(fd);
	if (close_err.type)
		err = error_priorize(err, redirect_print_and_qualify(close_err, false,
					"unable to close heredoc file"));
	if (err.type && unlink(path.data) != 0)
		(void)error_print(error_sys(), "unable to "
			"unlink heredoc file", NULL, "'%s'", path.data);
	if (err.type)
		return (string_free(&path), err);
	*out_path = path.data;
	return (err);
}
