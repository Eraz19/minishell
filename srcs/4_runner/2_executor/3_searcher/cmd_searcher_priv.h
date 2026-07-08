#ifndef CMD_SEARCHER_PRIV_H
# define CMD_SEARCHER_PRIV_H

# include "libft.h"
# include "error.h"
# include "cmd_cache.h"

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @brief Check whether a candidate path names an executable command.
 *
 * Missing paths are reported through the output flags and are not considered
 * errors.
 *
 * @param cmd_path Candidate command path to inspect (borrowed, read-only).
 * @param out_is_valid Destination receiving whether @p cmd_path is executable
 *                     (borrowed).
 * @param ref_found_but_not_executable Destination receiving whether a path was
 *                                     found but rejected as non-executable
 *                                     (borrowed).
 * @return @c ERR_NO or @c ERR_LIBC.
 */
t_error	cmd_check(
			const t_string *cmd_path,
			bool *out_is_valid,
			bool *ref_found_but_not_executable);

/**
 * @brief Accept an explicit command path containing a slash.
 *
 * @note @p ref_cmd_path must already be initialized by the caller.
 *
 * @param cmd_name Command name to inspect (borrowed, read-only).
 * @param ref_cmd_path Destination string updated in place (borrowed).
 * @return @c ERR_NO, @c ERR_POSIX_CMD_NOT_FOUND or @c ERR_LIBC.
 */
t_error	cmd_try_absolute_path(const t_string *cmd_name, t_string *ref_cmd_path);

/**
 * @brief Try to resolve a command through the command cache.
 *
 * Invalid cached entries are removed from @p cache before the function
 * returns.
 *
 * @note @p ref_cmd_path must already be initialized by the caller.
 *
 * @param cmd_name Command name to resolve (borrowed, read-only).
 * @param cache Command cache to query, or @c NULL (borrowed).
 * @param out_found_but_not_executable Destination receiving whether a cached
 *                                     path existed but was not executable
 *                                     (borrowed).
 * @param ref_cmd_path Destination string updated in place on success
 *                     (borrowed).
 * @return @c ERR_NO, @c ERR_POSIX_CMD_NOT_FOUND, @c ERR_POSIX_CMD_NOT_EXECUTABLE,
 *         @c ERR_SHELL_NOT_FOUND or @c ERR_LIBC.
 */
t_error	cmd_try_cache(
			const t_string *cmd_name,
			t_cmd_cache *cache,
			bool *out_found_but_not_executable,
			t_string *ref_cmd_path);

/**
 * @brief Search a command through the directories listed in @c PATH .
 *
 * Successful resolutions are inserted into @p cache when it is not @c NULL .
 *
 * @note @p ref_cmd_path must already be initialized by the caller.
 *
 * @param cmd_name Command name to resolve (borrowed, read-only).
 * @param cache Optional command cache to update, can be @c NULL (borrowed).
 * @param envp Environment array represented as a @ref t_vector of @c char*
 *             items (borrowed, read-only).
 * @param ref_cmd_path Destination string updated in place on success
 *                     (borrowed).
 * @return @c ERR_NO, @c ERR_POSIX_CMD_NOT_FOUND, @c ERR_POSIX_CMD_NOT_EXECUTABLE,
 *         @c ERR_SHELL_NOT_FOUND or @c ERR_LIBC.
 */
t_error	cmd_try_envp_path(
			const t_string *cmd_name,
			t_cmd_cache	*cache,
			const t_vector *envp,
			t_string *ref_cmd_path);

#endif
