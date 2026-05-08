#include "libft.h"
#include "builtins.h"
#include "posix_helpers.h"
#include <unistd.h>

#define SEPARATOR	": "

t_error	builtin_error_usage(
	const t_shell *shell,
	const char *builtin,
	const char *usage)
{
	const char	*prefix;

	prefix = error_to_string(ERR_BUILTIN_INVALID_USAGE);
	// TODO: (void)shell_print_name(STDERR_FILENO, shell);
	(void)shell;
	(void)posix_write(STDERR_FILENO, "minishell", str_len("minishell"));
	// EODO: end
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

t_error	builtin_error_flag(
	const t_shell *shell,
	const char *builtin,
	const char *flag)
{
	const char	*prefix;

	prefix = error_to_string(ERR_BUILTIN_INVALID_FLAG);
	// TODO: (void)shell_print_name(STDERR_FILENO, shell);
	(void)shell;
	(void)posix_write(STDERR_FILENO, "minishell", str_len("minishell"));
	// EODO: end
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

t_error	builtin_print_custom(
	const t_shell *shell,
	const char *builtin,
	const char *prefix,
	t_error error)
{
	const char	*message;

	message = error_to_string(error);
	// TODO: (void)shell_print_name(STDERR_FILENO, shell);
	(void)shell;
	(void)posix_write(STDERR_FILENO, "minishell", str_len("minishell"));
	// EODO: end
	(void)posix_write(STDERR_FILENO, SEPARATOR, str_len(SEPARATOR));
	(void)posix_write(STDERR_FILENO, builtin, str_len(builtin));
	(void)posix_write(STDERR_FILENO, SEPARATOR, str_len(SEPARATOR));
	if (prefix)
	{
		(void)posix_write(STDERR_FILENO, prefix, str_len(prefix));
		(void)posix_write(STDERR_FILENO, SEPARATOR, str_len(SEPARATOR));
	}
	(void)posix_write(STDERR_FILENO, builtin, str_len(builtin));
	(void)posix_write(STDERR_FILENO, message, str_len(message));
	(void)posix_write(STDERR_FILENO, "\n", str_len("\n"));
	return (error);
}
