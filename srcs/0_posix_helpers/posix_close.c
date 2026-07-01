#include "error.h"
#include "posix_helpers.h"
#include "shell.h"
#include <errno.h>
#include <unistd.h>

/*
** On Linux, close() releases the file descriptor even when it returns EINTR;
** retrying could close an unrelated descriptor that has meanwhile reused the
** same number. EINTR is therefore reported as success, never retried.
*/
t_error	posix_close(int fd)
{
	t_error	err;

	if (close(fd) == 0)
		return (error(ERR_NO));
	err = error_sys();
	if (err.saved_errno == EINTR)
		return (shell_should_interrupt());
	return (err);
}
