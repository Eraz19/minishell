#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include "history_file_.h"
#include "posix_helpers.h"

t_error	history_file_open(t_history_file *state, int *fd, int flags)
{
	if (state->path.len == 0)
		return (state->err);
	state->err = posix_open_with_mode(state->path.data, flags, 0644, fd);
	if (state->err.type == ERR_LIBC && state->err.saved_errno == ENOENT)
	{
		flags |= O_CREAT;
		state->err = posix_open_with_mode(state->path.data, flags, 0644, fd);
	}
	return (state->err);
}
