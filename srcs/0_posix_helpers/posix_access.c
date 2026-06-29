#include "error.h"
#include "posix_helpers.h"
#include "posix_helpers_priv.h"
#include <errno.h>
#include <stdbool.h>
#include <unistd.h>

/*
** Probes a path with access(amode). A successful check sets *ok to true.
** A genuine "not there" result (ENOENT / ENOTDIR) sets *ok to false and is
** reported as success, so callers can branch on *ok without inspecting errno.
** Any other failure (EACCES, EIO, EROFS, ...) is a real error: *ok is false
** and ERR_LIBC is returned with the errno preserved.
*/
t_error	posix_access(const char *path, int amode, bool *ok)
{
	t_error	err;

	*ok = false;
	while (true)
	{
		if (access(path, amode) == 0)
			return (*ok = true, error(ERR_NO));
		if (errno == EINTR)
		{
			err = posix_handle_eintr();
			if (err.type)
				return (err);
			continue ;
		}
		if (errno == ENOENT || errno == ENOTDIR)
			return (error(ERR_NO));
		return (error_sys());
	}
}
