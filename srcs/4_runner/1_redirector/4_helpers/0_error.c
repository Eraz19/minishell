#include "redirector_priv.h"

t_error	redirect_print_error(const char *message)
{
	return (error_print(error(ERR_POSIX_REDIRECTION),
		REDIRECTOR_MODULE_NAME,
		message, NULL, NULL));
}

t_error	redirect_print_error_all_fd_used(void)
{
	return (redirect_print_error("all file descriptors are already used"));
}
