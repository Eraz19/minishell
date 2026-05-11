#ifndef READONLY_PRIV_H
# define READONLY_PRIV_H

# include "shell.h"
# include "error.h"

// ERR_VAR_INVALID_NAME / ERR_VAR_MISSING_EQUAL / ERR_VAR_READ_ONLY / ERR_LIBC.
t_error	readonly_add(t_shell *shell, const char *builtin, const char *string);

// Errors can be ERR_LIBC.
t_error	readonly_print(const t_shell *shell, const char *builtin);

#endif
