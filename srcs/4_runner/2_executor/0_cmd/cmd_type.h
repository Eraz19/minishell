#ifndef CMD_TYPE_H
# define CMD_TYPE_H

# include "libft.h"
# include "builtins.h"
# include "functions.h"
# include <stdbool.h>

/**
 * @enum e_cmd_type
 * @brief Classification result stored inside @ref t_cmd.
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
 * @struct s_cmd
 * @brief Expanded and classified command descriptor used by the executor.
 *
 * @var s_cmd::name Command name view borrowed from the first entry of
 *                  @ref s_cmd::argv.
 * @var s_cmd::type Resolved command kind.
 * @var s_cmd::is_declaration_utility Whether the command name is a declaration
 *                                    utility such as @c export or
 *                                    @c readonly.
 * @var s_cmd::argv Expanded argument vector as a NUL-terminated array of owned
 *                  @c char * items.
 * @var s_cmd::envp Environment array built for command execution as a
 *                  NUL-terminated array of owned @c char * items.
 * @var s_cmd::path Resolved executable path for @c CMD_EXTERNAL commands
 *                  managed as a @ref t_string.
 * @var s_cmd::builtin Builtin entry point selected for builtin command kinds.
 * @var s_cmd::function Shell function selected for @c CMD_FUNCTION commands
 *                      (borrowed, read-only).
 */
typedef struct s_cmd
{
	/** @brief Command name view borrowed from the first @ref s_cmd::argv item. */
	t_string			name;
	/** @brief Resolved command kind. */
	t_cmd_type			type;
	/** @brief Whether the command name is treated as a declaration utility. */
	bool				is_declaration_utility;
	/** @brief Expanded argument vector stored as owned @c char * items. */
	t_vector			argv;
	/** @brief Execution environment stored as owned @c char * items. */
	t_vector			envp;
	/** @brief Resolved executable path for @c CMD_EXTERNAL commands. */
	t_string			path;
	/** @brief Builtin entry point for builtin command kinds. */
	t_builtin			builtin;
	/** @brief Resolved shell function for @c CMD_FUNCTION commands
	 *         (borrowed, read-only). */
	const t_function	*function;
	bool				path_is_temporary;
}	t_cmd;

#endif
