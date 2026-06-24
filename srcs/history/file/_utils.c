#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include "history_file_.h"

t_error	history_file_open(t_history_file *state, int *fd, int flags)
{
	*fd = open(state->path, flags, 0644);
	if (*fd == -1 && errno != ENOENT)
		return (state->err = error_sys());
	if (*fd == -1)
	{
		*fd = open(state->path, O_CREAT | flags, 0644);
		if (*fd == -1)
			return (state->err = error_sys());
	}
	return (state->err);
}
