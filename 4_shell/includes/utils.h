/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:23:46 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 12:38:30 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "libft.h"
# include "error.h"
# include <pwd.h>
# include <time.h>
# include "error.h"
# include "ft_getopt.h"

// TODO: doc (vector_deep_dup)

typedef t_error	(*t_dup_callback)(void *dst_item, const void *src_item);
typedef void	(*t_free_callback)(void *dst_item);

t_error	vector_deep_dup(
			t_vector *dst,
			const t_vector *src,
			t_dup_callback dup_callback,
			t_free_callback free_callback);

// TODO: doc (serach_file)

typedef enum e_file_type
{
	EXECUTABLE,
	READABLE
}	t_file_type;

// @ret ERR_FILE_NOT_FOUND / ERR_FILE_NOT_EXECUTABLE / ERR_FILE_NOT_READABLE
// 		/ ERR_LIBC
t_error	file_check(const char *filepath, t_file_type mode, bool *ref_found);

// @ret ERR_FILE_NOT_FOUND / ERR_FILE_NOT_EXECUTABLE / ERR_FILE_NOT_READABLE
// 		/ ERR_LIBC
t_error	file_search(
			const t_string *raw_path,
			const t_string *filename,
			t_file_type mode,
			t_string *out_file_path);

/**
 * @brief Test whether an environment entry matches a target variable name.
 *
 * The comparison succeeds when @p entry starts with @p target and both strings
 * end or continue with the same character at the first differing position,
 * which makes the helper suitable for matching @c NAME=... entries.
 *
 * @param target Variable name to match (borrowed, read-only).
 * @param entry Full environment entry to inspect (borrowed, read-only).
 * @return True when @p entry targets @p target, false otherwise.
 */
bool	assignment_is_same_name(const char *target, const char *entry);

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
 * @param dst_name Destination name string initialized by the function
 *					(borrowed).
 * @param dst_value Destination value string initialized by the function
 *					(borrowed).
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
 * @brief Parse short @c + and @c - options from @p argv.
 *
 * @note The function initializes @p out->options and, on success, the caller
 *       must release it with @c vector_free(&out->options, NULL).
 * @note This function always prints a diagnostic before returning an error.
 *
 * @param argc Argument count.
 * @param argv Argument array to parse, with the command name at index 0
 *             (borrowed, read-only).
 * @param input Parsing specification (borrowed, read-only).
 * @param out Destination initialized by the function on entry and filled on
 *            success (borrowed).
 * @return @c ERR_INVALID_USAGE @c ERR_UB or @c ERR_LIBC.
 */
t_error	ft_getopt(int argc, char **argv, t_getopt_in *input, t_getopt_out *out);

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
 * @brief Check whether @p name is a valid shell variable name.
 *
 * @param name Name to validate (borrowed, read-only).
 * @return True when @p name starts with an alphabetic character or @c _ and
 *         contains only alphanumeric characters or @c _ afterwards.
 */
bool	name_is_valid_str(const t_string *name);

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
