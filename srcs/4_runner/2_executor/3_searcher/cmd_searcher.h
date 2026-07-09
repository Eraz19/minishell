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
 * @p cache, then scans the directories listed in the @c PATH entry of
 * @p cmd->envp.
 *
 * @note @p cmd must already contain a resolved name and an initialized
 *       environment vector.
 * @note On success, @p cmd->path contains an owned executable path for
 *       external commands. The search may also rewrite @p cmd as a builtin
 *       when the resolved path matches a regular utility handled internally.
 *
 * @param cmd Command whose executable path must be resolved (borrowed).
 * @param cache Optional command cache, can be @c NULL (borrowed).
 * @return @c ERR_NO, @c ERR_POSIX_CMD_NOT_FOUND, @c ERR_POSIX_CMD_NOT_EXECUTABLE,
 *         @c ERR_SHELL_NOT_FOUND or @c ERR_LIBC.
 */
t_error	cmd_search(t_cmd *cmd, t_cmd_cache *cache);

#endif
