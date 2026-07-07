#ifndef CMD_RESOLVER_PRIV_H
# define CMD_RESOLVER_PRIV_H

# include "cmd_resolution_type.h"
# include "builtins.h"
# include "functions.h"
# include <stdbool.h>

/* ************************************************************************* */
/*                                LIFE CYCLE                                 */
/* ************************************************************************* */

/**
 * @brief Initialize an empty command resolution object.
 *
 * @note @p cmd_resolution is initialized by the function.
 *
 * @param cmd_resolution Destination resolution (borrowed, initialized by the
 *                       function).
 */
void	cmd_resolution_init(t_cmd_resolution *cmd_resolution);

/**
 * @brief Release every resource stored in a command resolution object.
 *
 * @param cmd_resolution Resolution to free (borrowed).
 */
void	cmd_resolution_free(t_cmd_resolution *cmd_resolution);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

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
 * @brief Test whether a command name falls into the POSIX unspecified set.
 *
 * @note When the name matches this set, the function reports undefined
 *       behaviour through the error subsystem before returning.
 *
 * @param name Command name to classify (borrowed, read-only).
 * @return True when the result is specified as unspecified by POSIX, false
 *         otherwise.
 */
bool	cmd_name_is_unspecified(const char *name);

/**
 * @brief Test whether a command name resolves to a shell function.
 *
 * @param functions Function table to query (borrowed).
 * @param name Command name to classify (borrowed, read-only).
 * @param out_function Destination receiving the borrowed function or left
 *                     unchanged when not found (borrowed).
 * @return True when @p name resolves to a shell function, false otherwise.
 */
bool	cmd_name_is_function(
			t_functions *functions,
			const char *name,
			const t_function **out_function);

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

#endif
