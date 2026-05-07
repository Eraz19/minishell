#include "libft.h"
#include "posix_helpers.h"
#include <unistd.h>

void	builtin_print_usage(const char *name, const char *usage)
{
	static const char	prefix[] = ": usage: ";

	(void)posix_write(STDERR_FILENO, name, str_len(name));
	(void)posix_write(STDERR_FILENO, prefix, str_len(prefix));
	(void)posix_write(STDERR_FILENO, name, str_len(name));
	(void)posix_write(STDERR_FILENO, usage, str_len(usage));
}
