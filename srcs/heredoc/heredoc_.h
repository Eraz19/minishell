#ifndef HEREDOC__H
# define HEREDOC__H

# include "error.h"
# include "token.h"
# include "heredoc.h"

/** @defgroup heredoc_priv Heredoc internals
 *  @brief Backing file creation, delimiter expansion and error
 *         requalification behind the heredoc API.
 */

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
