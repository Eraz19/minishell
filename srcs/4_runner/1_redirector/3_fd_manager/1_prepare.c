#include "fd_tracker.h"
#include "redirector_type.h"
#include "fd_manager.h"

t_error	fd_prepare_perm(t_redirector *redirector, int fd)
{
	t_error	err;

	if (fd < TRACKER_MIN_FD_SHELL)
		return (error(ERR_NO));
	err = fd_tracker_protect(&redirector->tracker, fd);
	if (err.type)
		return (err);
	return (fd_tracker_grow(&redirector->tracker, (size_t)fd + 1));
}
