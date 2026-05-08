#ifndef EXPORT_PRIV_H
# define EXPORT_PRIV_H

# include "builtins.h"

t_error	export_add(
	t_shell *shell,
	const char *builtin,
	const char *string);
t_error	export_print(const t_shell *shell, const char *builtin);

#endif
