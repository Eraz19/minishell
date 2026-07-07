#ifndef CMD_RESOLUTION_TYPE_H
# define CMD_RESOLUTION_TYPE_H

# include "cmd_expansion.h"
# include "builtins.h"
# include "functions.h"
# include <stdbool.h>

/**
 * @enum e_cmd_type
 * @brief Classification result produced by @ref cmd_resolve().
 */
typedef enum e_cmd_type
{
	CMD_NONE,
	CMD_SPECIAL_BUILTIN,
	CMD_UNSPECIFIED,
	CMD_FUNCTION,
	CMD_BUILTIN,
	CMD_EXTERNAL
}	t_cmd_type;

/**
 * @struct s_cmd_resolution
 * @brief Resolved command descriptor used by the executor.
 *
 * @var s_cmd_resolution::type Resolved command kind.
 * @var s_cmd_resolution::expansions Expanded command words managed by the
 *                                   cmd_expansion submodule.
 * @var s_cmd_resolution::path Resolved executable path for @c CMD_EXTERNAL
 *                             commands (owned).
 * @var s_cmd_resolution::builtin Builtin entry point selected for builtin
 *                                command kinds.
 * @var s_cmd_resolution::function Shell function selected for @c CMD_FUNCTION
 *                                 commands (borrowed, read-only).
 * @var s_cmd_resolution::is_declaration_utility Whether the command name is a
 *                                               declaration utility such as
 *                                               @c export or @c readonly.
 */
typedef struct s_cmd_resolution
{
	/** @brief Resolved command kind. */
	t_cmd_type			type;
	/** @brief Expanded words managed by the cmd_expansion submodule. */
	t_cmd_expansions	expansions;
	/** @brief Resolved executable path for @c CMD_EXTERNAL commands (owned). */
	char				*path;
	/** @brief Builtin entry point for builtin command kinds. */
	t_builtin			builtin;
	/** @brief Resolved shell function for @c CMD_FUNCTION commands
	 *         (borrowed, read-only). */
	const t_function	*function;
	/** @brief Whether the command name is treated as a declaration utility. */
	bool				is_declaration_utility;
}	t_cmd_resolution;

#endif
