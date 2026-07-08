#ifndef CMD_CACHE_H
# define CMD_CACHE_H

# include "libft.h"
# include "error.h"

/* ************************************************************************* */
/*                                   TYPES                                   */
/* ************************************************************************* */

/**
 * @brief Command lookup cache backed by a @ref t_hashmap.
 */
typedef t_hashmap	t_cmd_cache;

/* ************************************************************************* */
/*                                LIFE CYCLE                                 */
/* ************************************************************************* */

/**
 * @brief Initialize an empty command cache.
 *
 * @param cache Destination cache (borrowed, initialized by the function).
 */
void	cmd_cache_init(t_cmd_cache *cache);

/**
 * @brief Release the whole command cache and every cached path.
 *
 * @param cache Cache to free (borrowed).
 */
void	cmd_cache_free(t_cmd_cache *cache);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @brief Remove every cached entry while keeping the cache initialized.
 *
 * @param cache Cache to clear (borrowed).
 */
void	cmd_cache_clear(t_cmd_cache *cache);

/**
 * @brief Clear the command cache stored in the current shell runner.
 *
 * @return @c ERR_NO or @c ERR_SHELL_NOT_FOUND.
 */
t_error	cmd_cache_clear_void(void);

/**
 * @brief Read a cached command path.
 *
 * @note The returned path is borrowed from @p cache and becomes invalid if the
 *       entry is removed, replaced, or if @p cache is cleared or freed.
 *
 * @param cache Cache to query (borrowed, read-only).
 * @param cmd_name Command name to look up (borrowed, read-only).
 * @param out_cmd_path Destination receiving the borrowed cached path or
 *                     @c NULL (borrowed).
 * @return @c ERR_NO when a cached path is found, @c ERR_CMD_NOT_FOUND when
 *         command hashing is disabled or when @p cmd_name is not cached, or
 *         @c ERR_SHELL_NOT_FOUND / @c ERR_LIBC on option lookup failure.
 */
t_error	cmd_cache_get(
			const t_cmd_cache *cache,
			const t_string *cmd_name,
			const t_string **out_cmd_path);

/**
 * @brief Store a command path in the cache.
 *
 * When the @c OPT_CMD_HASH option is enabled, the cache stores a deep copy of
 * @p cmd_path. The caller keeps ownership of @p cmd_path in every case.
 *
 * @note When command hashing is disabled, the function returns @c ERR_NO and
 *       leaves @p cache unchanged.
 *
 * @param cache Cache to update (borrowed).
 * @param cmd_name Command name used as cache key (borrowed, read-only).
 * @param cmd_path Command path to cache (borrowed, read-only).
 * @return @c ERR_NO on success or when command hashing is disabled, or
 *         @c ERR_SHELL_NOT_FOUND / @c ERR_LIBC on failure.
 */
t_error	cmd_cache_set(
			t_cmd_cache *cache,
			const t_string *cmd_name,
			const t_string *cmd_path);

/**
 * @brief Remove a cached command path.
 *
 * If @p cmd_name is not present, the function does nothing.
 *
 * @param cache Cache to update (borrowed).
 * @param cmd_name Command name to remove (borrowed, read-only).
 */
void	cmd_cache_unset(t_cmd_cache *cache, const t_string *cmd_name);

#endif
