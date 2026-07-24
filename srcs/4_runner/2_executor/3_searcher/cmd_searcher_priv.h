#ifndef CMD_SEARCHER_PRIV_H
# define CMD_SEARCHER_PRIV_H

# include "error.h"
# include "cmd_cache.h"
# include "cmd_type.h"

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @brief Accept @p cmd->name directly when it already contains a @c /.
 *
 * @warning @p cmd->path must already be initialized by the caller.
 *
 * @param cmd Command being resolved in place (borrowed).
 * @return @c ERR_NO when @p cmd->name is duplicated into @p cmd->path,
 *         @c ERR_POSIX_CMD_NOT_FOUND when @p cmd->name does not contain
 *         a @c /, or @c ERR_LIBC on allocation failure.
 */
t_error	cmd_try_absolute_path(t_cmd *cmd);

/**
 * @brief Resolve @p cmd from the command cache.
 *
 * @note On success, the cached path is duplicated into @p cmd->path. The
 *       function may also rewrite @p cmd as a builtin through
 *       @ref cmd_try_regular_builtin().
 *
 * @param cmd Command being resolved in place (borrowed).
 * @param cache Cache to query, can be @c NULL (borrowed).
 * @return @c ERR_NO, @c ERR_POSIX_CMD_NOT_FOUND,
 *         @c ERR_POSIX_CMD_NOT_EXECUTABLE, @c ERR_SHELL_NOT_FOUND or
 *         @c ERR_LIBC.
 */
t_error	cmd_try_cache(t_cmd *cmd, t_cmd_cache *cache);

/**
 * @brief Resolve @p cmd by scanning the directories listed in @c PATH.
 *
 * @note Empty @c PATH components are interpreted as the current directory.
 * @note On success, the resolved path is stored in @p cmd->path unless the
 *       match is rewritten as a builtin by @ref cmd_try_regular_builtin().
 *
 * @param cmd Command being resolved in place (borrowed).
 * @param cache Cache optionally updated on successful external resolution
 *              (borrowed).
 * @return @c ERR_NO, @c ERR_POSIX_CMD_NOT_FOUND,
 *         @c ERR_POSIX_CMD_NOT_EXECUTABLE, @c ERR_SHELL_NOT_FOUND or
 *         @c ERR_LIBC.
 */
t_error	cmd_try_envp_path(t_cmd *cmd, t_cmd_cache *cache);

/**
 * @brief Rewrite some resolved regular utilities as internal builtins.
 *
 * When @p cmd->path matches one of the hard-coded regular utility paths, the
 * function sets @p cmd->type to @c CMD_BUILTIN, assigns the builtin entry
 * point, and releases @p cmd->path.
 *
 * @param cmd Command to rewrite in place (borrowed).
 */
void	cmd_try_regular_builtin(t_cmd *cmd);

#endif
