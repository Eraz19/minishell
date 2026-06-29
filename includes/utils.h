#ifndef UTILS_H
# define UTILS_H

# include "libft.h"
# include "error.h"
# include <pwd.h>
# include <time.h>
# include "error.h"

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @brief Split an assignment string into name and value parts.
 *
 * @p src is split at the first @c =. If no separator is present, @p dst_value
 * is left empty. The caller owns both resulting strings on success and must
 * release them with @ref string_free().
 *
 * @param src Assignment string (borrowed, read-only).
 * @param dst_name Destination name string initialized by the function (borrowed).
 * @param dst_value Destination value string initialized by the function (borrowed).
 * @return @c ERR_ASSIGNMENT_MISSING_NAME or @c ERR_LIBC on failure.
 */
t_error	assignment_split(
			const char *src,
			t_string *dst_name,
			t_string *dst_value);

/**
 * @brief Deserialize a quoted string into a fresh string.
 *
 * The caller owns the resulting string on success and must release it with
 * @ref string_free().
 *
 * @param src Quoted source string (borrowed, read-only).
 * @param dst Destination string initialized by the function (borrowed).
 * @return @c ERR_FORMAT_INVALID or @c ERR_LIBC on failure.
 */
t_error	deserialize(const char *src, t_string *dst);

/**
 * @brief Deserialize a newline-separated block of quoted strings into a vector.
 *
 * Malformed entries are skipped; only allocation failures stop the parse.
 * The caller owns each @ref t_string entry and must free the vector with
 * @ref vector_free() using @ref string_free_void() as callback.
 *
 * @param src Serialized block (borrowed, read-only).
 * @param dst Destination vector initialized by the function (borrowed).
 * @return @c ERR_LIBC on failure.
 */
t_error	deserialize_all(const char *src, t_vector *dst);

/**
 * @brief Look up a passwd entry in @c /etc/passwd.
 *
 * The returned pointer refers to static storage and is overwritten by the
 * next call.
 *
 * @param name Login name (borrowed, read-only).
 * @return Matching entry, or @c NULL if @p name is @c NULL, @c /etc/passwd
 *         cannot be read, or no entry matches.
 */
struct passwd	*ft_getpwnam(const char *name);

/**
 * @brief Get the current Unix time in seconds.
 *
 * @return Current Unix time, or @c -1 on system-call failure.
 */
time_t	get_now_unix_seconds(void);

/**
 * @brief Check whether @p name is a valid shell variable name.
 *
 * @param name Name to validate (borrowed, read-only).
 * @return True when @p name starts with an alphabetic character or @c _ and
 *         contains only alphanumeric characters or @c _ afterwards.
 */
bool	name_is_valid(const t_string *name);

/**
 * @brief Const-string variant of @ref name_is_valid().
 *
 * @param name Name to validate (borrowed, read-only).
 * @return True when @p name starts with an alphabetic character or @c _ and
 *         contains only alphanumeric characters or @c _ afterwards.
 */
bool	name_is_valid_from_const(const char *name);

/**
 * @brief Serialize a string into a single-quoted representation.
 *
 * The caller owns the resulting string on success and must release it with
 * @ref string_free().
 *
 * @param src Source string (borrowed, read-only).
 * @param dst Destination string initialized by the function (borrowed).
 * @return @c ERR_NO or @c ERR_LIBC.
 */
t_error	serialize(const char *src, t_string *dst);

#endif
