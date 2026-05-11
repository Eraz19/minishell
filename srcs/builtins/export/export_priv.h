#ifndef EXPORT_PRIV_H
# define EXPORT_PRIV_H

# include "error.h"
# include "shell.h"

// ERR_VAR_INVALID_NAME / ERR_VAR_READ_ONLY / ERR_VAR_MISSING_EQUAL / ERR_LIBC.
t_error	export_add(t_shell *shell, const char *builtin, const char *string);

// Errors can be ERR_LIBC.
t_error	export_print(const t_shell *shell, const char *builtin);

#endif
