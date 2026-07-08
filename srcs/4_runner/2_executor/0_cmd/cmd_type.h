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
 * @var s_cmd::name Command name view into the first expanded argument,
 *                  managed by the @c cmd_resolver submodule.
 * @var s_cmd::type Command kind selected by the @c cmd_resolver submodule.
 * @var s_cmd::is_declaration_utility Whether the resolved name behaves as a
 *                                    declaration utility, managed by the
 *                                    @c cmd_resolver submodule.
 * @var s_cmd::argv Expanded argument vector stored as owned @c char * items,
 *                  managed by the @c cmd_resolver submodule.
 * @var s_cmd::envp Execution environment stored as owned @c char * items,
 *                  managed by the @c cmd_assignator submodule.
 * @var s_cmd::path Executable path for @c CMD_EXTERNAL commands, managed by
 *                  the @c cmd_searcher submodule.
 * @var s_cmd::builtin Builtin entry point selected by the @c cmd_resolver
 *                     submodule.
 * @var s_cmd::function Shell function selected by the @c cmd_resolver
 *                      submodule (borrowed, read-only).
 * @var s_cmd::path_is_temporary Whether @c PATH was overridden by assignment
 *                               words for the current command, managed by the
 *                               @c cmd_assignator submodule.
 * @var s_cmd::exit_status Command status produced by the
 *                         @c cmd_dispatcher submodule.
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
	/** @brief Whether assignment words override @c PATH for this command. */
	bool				path_is_temporary;
	/** @brief Exit status produced when the command is dispatched. */
	int					exit_status;
}	t_cmd;

#endif
