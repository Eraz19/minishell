#ifndef CMD_RESOLVER_PRIV_H
# define CMD_RESOLVER_PRIV_H

# include "builtins.h"
# include "functions.h"
# include <stdbool.h>

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @brief Test whether a command name resolves to a shell function.
 *
 * @param functions Function table to query (borrowed, read-only).
 * @param name Command name to classify (borrowed, read-only).
 * @param out_function Destination receiving the borrowed function or left
 *                     unchanged when not found (borrowed).
 * @return True when @p name resolves to a shell function, false otherwise.
 */
bool	cmd_name_is_function(
			const t_functions *functions,
			const char *name,
			t_function **out_function);

/**
 * @brief Test whether a command name is an intrinsic builtin.
 *
 * @param name Command name to classify (borrowed, read-only).
 * @param out_builtin Destination receiving the builtin entry point or @c NULL
 *                    (borrowed).
 * @return True when @p name is an intrinsic builtin, false otherwise.
 */
bool	cmd_name_is_intrinsic_builtin(const char *name, t_builtin *out_builtin);

/**
 * @brief Test whether a command name is a regular builtin.
 *
 * @param name Command name to classify (borrowed, read-only).
 * @param out_builtin Destination receiving the builtin entry point or @c NULL
 *                    (borrowed).
 * @return True when @p name is a regular builtin, false otherwise.
 */
bool	cmd_name_is_regular_builtin(const char *name, t_builtin *out_builtin);

/**
 * @brief Test whether a command name is a POSIX special builtin.
 *
 * @param name Command name to classify (borrowed, read-only).
 * @param out_builtin Destination receiving the builtin entry point or @c NULL
 *                    (borrowed).
 * @return True when @p name is a special builtin, false otherwise.
 */
bool	cmd_name_is_special_builtin(const char *name, t_builtin *out_builtin);

/**
 * @brief Warn when @p name matches a command name with unspecified POSIX
 *        resolution semantics.
 *
 * @note The warning is emitted only for names listed by POSIX 2.9.1.4 as
 *       producing unspecified results when used as command names.
 *
 * @param name Command name to inspect (borrowed, read-only).
 */
void	cmd_warn_if_unspecified(const char *name);

#endif
