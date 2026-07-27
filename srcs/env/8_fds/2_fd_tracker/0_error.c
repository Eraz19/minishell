#include "fd_tracker_priv.h"

#define ALL_FDS_USED	"all file descriptors are already used"

t_error	redirect_print_error_all_fd_used(void)
{
	return (error_print(error(ERR_REDIRECTION), ALL_FDS_USED, NULL, NULL));
}
