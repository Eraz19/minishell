#include "error.h"
#include "shell.h"

t_error	posix_handle_eintr(void)
{
	bool	should_interrupt;
	t_error	err;

	err = shell_should_interrupt(&should_interrupt);
	if (err.type)
		return (err);
	else if (should_interrupt)
		return (error(ERR_INTERRUPTED));
	return (error(ERR_NO));
}
