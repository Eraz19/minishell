#include "xtrace_priv.h"
#include "posix_helpers.h"
#include <unistd.h>

t_error	xtrace_print_content(const t_string *string, size_t i, size_t count)
{
	t_error	err;

	if (string->len == 0)
		return (error(ERR_NO));
	err = posix_write(STDERR_FILENO, string->data, string->len);
	if (err.type)
		return (err);
	else if (i < count - 1)
		return (posix_write(STDERR_FILENO, " ", 1));
	else
		return (posix_write(STDERR_FILENO, "\n", 1));
	return (err);
}
