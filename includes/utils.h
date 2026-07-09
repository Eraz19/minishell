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
 * @brief Free a @c char* item through a generic @c void* callback signature.
 *
 * Wrapper around @c free() intended for containers storing @c char* items,
 * such as @ref t_vector.
 *
 * @warning @p ptr must point to a valid @c char* slot.
 *
 * @param ptr Pointer to a @c char* item passed as @c void* (borrowed).
 */
void	free_char_ptr_void(void *ptr);

/**
 * @brief Look up a passwd entry by login name using @c /etc/passwd.
 *
 * On success, @p out_pw receives either a borrowed pointer to internal static
 * storage when a matching entry exists, or @c NULL when @p name is @c NULL or
 * no entry matches.
 *
 * @warning The returned passwd structure is invalidated by the next call to
 *          @ref ft_getpwnam().
 *
 * @param name Login name to search, or @c NULL to skip lookup
 *             (borrowed, read-only).
 * @param out_pw Destination receiving the borrowed passwd entry or @c NULL
 *               (borrowed).
 * @return @c ERR_NO, @c ERR_INTERRUPTED or @c ERR_LIBC.
 */
t_error	ft_getpwnam(const char *name, struct passwd **out_pw);

/**
 * @brief Get the current Unix time in seconds.
 *
 * @return Current Unix time, or @c -1 on system-call failure.
 */
time_t	get_now_unix_seconds(void);

/**
 * @brief Match the first @p len characters of @p str against the whole POSIX
 *        shell pattern @p pattern.
 *
 * Supports @c * and @c ? wildcards, @c \ escapes, and bracket expressions
 * (@c ! or @c ^ negation, ranges, character classes @c [:alpha:], collating
 * symbols @c [.x.] and equivalence classes @c [=x=]).
 *
 * @note Only the first @p len characters of @p str are read, so @p str need
 *       not be NUL-terminated; the whole slice must match the whole
 *       @p pattern.
 * @param pattern NUL-terminated pattern C-string (borrowed, read-only).
 * @param str Characters to match, at least @p len long (borrowed, read-only).
 * @param len Number of characters of @p str to match.
 * @return True when the @p len first characters of @p str match @p pattern
 *         entirely.
 */
bool	match_pattern(const char *pattern, const char *str, size_t len);

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

/**
 * @brief Check that a bracket expression is properly closed and measure its
 *        length, honouring @c ! / @c ^ negation, a leading literal @c ],
 *        @c \ escapes and @c [: @c :], @c [. @c .], @c [= @c =]
 *        sub-expressions.
 *
 * @param pattern NUL-terminated C-string pointing just after the opening
 *                @c [ of the expression (borrowed, read-only).
 * @param len In: offset in @p pattern where scanning starts (usually @c 0);
 *            out: offset of the closing @c ] on success, of the NUL
 *            terminator on failure (borrowed).
 * @return True when the bracket expression is terminated by @c ].
 */
bool	valid_bracket_exp_len(const char *pattern, size_t *len);

#endif
