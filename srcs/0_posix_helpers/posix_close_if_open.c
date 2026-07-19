#include "error.h"
#include "posix_helpers.h"
#include <errno.h>
#include <unistd.h>

/*
** POSIX.1-2024 / The Open Group Base Specifications Issue 8 changed the
** historical close()+EINTR ambiguity.
**
** Older POSIX text specified that if close() was interrupted by a caught
** signal, close() returned -1 with errno set to EINTR and "the state of fildes
** is unspecified". In POSIX.1-2024, EINTR is the restartable case: if close()
** returns -1 with errno set to EINTR, the file descriptor remains open; if the
** descriptor is being closed/closed, the error is reported with EINPROGRESS
** instead.
**
** The POSIX.1-2024 posix_close() interface, together with POSIX_CLOSE_RESTART,
** would make this easier to control, but posix_close() is forbidden by the
** project whitelist. This wrapper therefore uses close() directly.
**
** This shell is single-threaded. Its signal handlers never open, duplicate, or
** close file descriptors; they only set volatile sig_atomic_t flags. Therefore,
** no signal handler can reuse fd while this function is retrying close().
**
** The fd tracker requires a definitive final state:
** - close() == 0 means fd is closed: success.
** - EBADF means fd was already closed/invalid: success for close_if_open().
** - EINTR is retried because POSIX.1-2024 says fd remains open.
** - EINPROGRESS is retried as a project-level recovery choice: if the close
**   completes, a later retry should reach either success or EBADF; if it fails
**   with another errno, the fd tracker can no longer guarantee a coherent
**   state.
** - any errno other than EINTR, EINPROGRESS, or EBADF is reported as failure
**   and should be treated as non-recoverable by critical fd-tracker callers.
*/
t_error	posix_close_if_open(int fd)
{
	if (fd < 0)
		return (error(ERR_NO));
	while (true)
	{
		if (close(fd) == 0 || errno == EBADF)
			return (error(ERR_NO));
		else if (errno == EINTR || errno == EINPROGRESS)
			continue ;
		return (error_sys());
	}
}

