#include <errno.h>
#include <fcntl.h>
#include "history_file_.h"
#include "posix_helpers.h"

t_error	history_file_open(t_history_file *state, int *fd, int flags)
{
	state->err = posix_open(state->path.data, flags, fd);
	if (state->err.type && state->err.saved_errno != ENOENT)
		return (state->err);
	if (*fd == -1)
	{
		state->err = posix_open_with_mode(
				state->path.data, O_CREAT | flags, 0644, fd);
		if (state->err.type)
			return (state->err);
	}
	return (state->err);
}
