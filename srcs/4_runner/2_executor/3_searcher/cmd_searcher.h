#ifndef CMD_SEARCHER_H
# define CMD_SEARCHER_H

# include "error.h"
# include "cmd_type.h"
# include "cmd_cache.h"

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @brief Resolve the executable path stored in @p cmd.
 *
 * The search first accepts explicit paths containing @c /, then checks
 * @p cache, then scans the directories listed in @p cmd->envp @c PATH.
 *
 * @note @p cmd must already contain a resolved name and an initialized
 *       environment.
 * @note On success, @p cmd->path contains an owned path managed by
 *       @ref cmd_free().
 *
 * @param cmd Command whose executable path must be resolved (borrowed).
 * @param cache Optional command cache, can be @c NULL (borrowed).
 * @return @c ERR_NO, @c ERR_POSIX_CMD_NOT_FOUND, @c ERR_POSIX_CMD_NOT_EXECUTABLE,
 *         @c ERR_SHELL_NOT_FOUND or @c ERR_LIBC.
 */
t_error	cmd_search(t_cmd *cmd, t_cmd_cache *cache);

#endif
