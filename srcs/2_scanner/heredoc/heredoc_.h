#ifndef HEREDOC__H
# define HEREDOC__H

# include "error.h"

/** @defgroup heredoc_priv Heredoc internals
 *  @brief Backing file creation, delimiter expansion and error
 *         requalification behind the heredoc API.
 */

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
