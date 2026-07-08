#ifndef CMD_SEARCHER_H
# define CMD_SEARCHER_H

# include "error.h"
# include "cmd_type.h"
# include "cmd_cache.h"

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @brief Resolve a command name to an executable path.
 *
 * The search first accepts explicit paths containing @c /, then checks the
 * command cache, then scans the directories listed in @p envp @c PATH.
 *
 * @note @p out_cmd_path is initialized by the function.
 * @note On success, @p out_cmd_path contains an owned path and must later be
 *       released with @ref string_free().
 *
 * @param cmd_name Command name or path to resolve (borrowed, read-only).
 * @param envp Environment array represented as a @ref t_vector of @c char*
 *             items (borrowed, read-only).
 * @param cache Optional command cache, can be @c NULL (borrowed).
 * @param out_cmd_path Destination string initialized by the function
 *                     (borrowed).
 * @return @c ERR_NO, @c ERR_CMD_NOT_FOUND, @c ERR_CMD_NOT_EXECUTABLE,
 *         @c ERR_SHELL_NOT_FOUND or @c ERR_LIBC.
 */
t_error	cmd_search(t_cmd *cmd, t_cmd_cache *cache);

#endif
