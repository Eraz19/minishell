#ifndef HEREDOC__H
# define HEREDOC__H

# include "error.h"
# include "heredoc.h"

# define HEREDOC_TMP_PATH "/tmp/minishell_heredoc_"

/** @defgroup heredoc_priv Heredoc internals
 *  @brief Backing file creation, delimiter expansion and error
 *         requalification behind the heredoc API.
 */

/* ************************************************************************* */
/*                                   FILE                                    */
/* ************************************************************************* */

/**
 * @ingroup heredoc_priv
 * @brief Creates the next free backing file
 *        (@c HEREDOC_TMP_PATH + increasing identifier, mode 0600) and
 *        returns its path.
 *
 * @param heredoc Heredoc state (borrowed).
 * @param path String receiving the file path, initialized by the function
 *             and freed on failure (borrowed).
 * @return @c ERR_HEREDOC_MAX_ID_REACHED (printed) when every identifier
 *         up to @c INT_MAX is taken; @c ERR_LIBC (printed) on a creation
 *         failure; @c ERR_INTERRUPTED when a signal interrupts the
 *         creation; @c ERR_NO on success.
 */
t_error	create_heredoc_file(t_heredoc *heredoc, t_string *path);

/* ************************************************************************* */
/*                                 EXPANSION                                 */
/* ************************************************************************* */

/**
 * @ingroup heredoc_priv
 * @brief Quote-removes the here-document delimiter and appends the
 *        trailing newline used by the delimiter line comparison.
 *
 * @param heredoc Heredoc state (borrowed).
 * @param out String receiving the expanded delimiter, initialized by the
 *            function on success (borrowed).
 * @param delim Raw delimiter token (borrowed, read-only).
 * @return From the quote removal, qualified by the expander:
 *         @c ERR_POSIX_EXPANSION (printed), @c ERR_INTERNAL (printed),
 *         @c ERR_LIBC (printed) or @c ERR_INTERRUPTED; @c ERR_LIBC (raw)
 *         if the newline append fails; @c ERR_NO on success.
 */
t_error	expand_delim(t_heredoc *heredoc, t_string *out, const t_token *delim);

/**
 * @ingroup heredoc_priv
 * @brief Builds the expansion flag set of a here-document body
 *        (POSIX 2.7.4): parameter, command and arithmetic expansion plus
 *        quote removal, and @c EXP_HEREDOC so the body is re-lexed with
 *        the here-document rules; no field splitting, no pathname
 *        expansion.
 *
 * @return The flag set.
 */
uint	generate_heredoc_body_expand_flags(void);

/* ************************************************************************* */
/*                                   ERROR                                   */
/* ************************************************************************* */

/**
 * @ingroup heredoc_priv
 * @brief Requalifies an error escaping the execution-time heredoc API
 *        (@c heredoc_expand_body, @c heredoc_load), whose callers no
 *        longer need the specifics.
 *
 * Prints the specific diagnostic at the moment precision is lost, then
 * requalifies: user-facing expansion failures become
 * @c ERR_POSIX_EXPANSION, temp-file write failures become
 * @c ERR_REDIRECTION (further requalified by the executor per error.h),
 * any other unqualified error becomes @c ERR_INTERNAL. @c ERR_LIBC is
 * printed with the heredoc context and kept, fully qualified errors
 * (>= @c ERR_INTERRUPTED) pass through untouched.
 *
 * @note The tokenization-side endpoints (@c heredoc_register,
 *       @c heredoc_read_body_from_input, @c heredoc_prepare_for_expansion)
 *       must NOT use it: their callers (scanner, expander) are the
 *       requalifiers and need the specific types.
 *
 * @param err Error to requalify.
 * @return The requalified (and printed) error.
 */
t_error	heredoc_error_qualify(t_error err);

#endif
