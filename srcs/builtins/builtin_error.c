#include "error.h"
#include "shell.h"
#include "posix_helpers.h"
#include <unistd.h>

#define SEPARATOR	": "

t_error	builtin_error_usage(const char *builtin, const char *usage)
{
	const char	*shell_name;
	const char	*prefix;

	prefix = error_to_string(ERR_BUILTIN_INVALID_USAGE);
	shell_name = shell_get_name();
	(void)posix_write(STDERR_FILENO, shell_name, str_len(shell_name));
	(void)posix_write(STDERR_FILENO, SEPARATOR, str_len(SEPARATOR));
	(void)posix_write(STDERR_FILENO, builtin, str_len(builtin));
	(void)posix_write(STDERR_FILENO, SEPARATOR, str_len(SEPARATOR));
	(void)posix_write(STDERR_FILENO, prefix, str_len(prefix));
	(void)posix_write(STDERR_FILENO, SEPARATOR, str_len(SEPARATOR));
	(void)posix_write(STDERR_FILENO, builtin, str_len(builtin));
	(void)posix_write(STDERR_FILENO, usage, str_len(usage));
	(void)posix_write(STDERR_FILENO, "\n", str_len("\n"));
	return (ERR_BUILTIN_INVALID_USAGE);
}

t_error	builtin_error_flag(const char *builtin, const char *flag)
{
	const char	*shell_name;
	const char	*prefix;

	prefix = error_to_string(ERR_BUILTIN_INVALID_FLAG);
	shell_name = shell_get_name();
	(void)posix_write(STDERR_FILENO, shell_name, str_len(shell_name));
	(void)posix_write(STDERR_FILENO, SEPARATOR, str_len(SEPARATOR));
	(void)posix_write(STDERR_FILENO, builtin, str_len(builtin));
	(void)posix_write(STDERR_FILENO, SEPARATOR, str_len(SEPARATOR));
	(void)posix_write(STDERR_FILENO, prefix, str_len(prefix));
	(void)posix_write(STDERR_FILENO, SEPARATOR, str_len(SEPARATOR));
	(void)posix_write(STDERR_FILENO, builtin, str_len(builtin));
	(void)posix_write(STDERR_FILENO, flag, str_len(flag));
	(void)posix_write(STDERR_FILENO, "\n", str_len("\n"));
	return (ERR_BUILTIN_INVALID_FLAG);
}
