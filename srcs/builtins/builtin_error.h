#ifndef BUILTIN_USAGE_H
# define BUILTIN_USAGE_H

#include "error.h"
#include "shell.h"

t_error	builtin_print_usage(
	const t_shell *shell,
	const char *builtin,
	const char *usage);

t_error	builtin_print_flag(
	const t_shell *shell,
	const char *builtin,
	const char *flag);

// prefix can be NULL
t_error	builtin_print_custom(
	const t_shell *shell,
	const char *builtin,
	const char *prefix,
	t_error error);

#endif
