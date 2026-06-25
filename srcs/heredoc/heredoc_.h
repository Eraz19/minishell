#ifndef HEREDOC__H
# define HEREDOC__H

# include "error.h"
# include "heredoc.h"

# define HEREDOC_TMP_PATH "/home/alexander/Documents/42/common_core/minishell/heredoc_"//"/tmp/minishell_heredoc_"

/**
 * @ingroup heredoc
 * @brief Creates a fresh, uniquely named temporary file for a heredoc body.
 *
 * Builds a path from the state's monotonic counter and opens it with
 * O_CREAT | O_EXCL; on a name clash it bumps the counter and retries, so the
 * returned path is guaranteed not to collide with an existing file. The file
 * is created empty and closed immediately; the body is written later.
 *
 * @param state Pointer to the heredoc state (borrowed); its file counter is
 *              advanced.
 * @param path Out-parameter receiving the newly allocated path (owned by the
 *             caller on success, freed internally on failure).
 * @return ERR_NO on success, or ERR_LIBC on allocation or open failure.
 */
t_error	heredoc_create_file(t_heredoc *state, t_buff *path);

/**
 * @ingroup heredoc
 * @brief Turns a raw delimiter word into the string body lines match against.
 *
 * Removes the quotes from @p *delim and appends a trailing newline, so the
 * result matches a whole body line exactly. On success the old @p *delim is
 * replaced by a freshly allocated string; the previous pointer is not freed
 * here (the caller owns whatever it passed in).
 *
 * @param state Pointer to the heredoc state (borrowed).
 * @param delim In/out delimiter; on success @p *delim points to a new owned
 *              string, on failure it is left untouched.
 * @return ERR_NO on success, or ERR_LIBC on allocation failure.
 */
t_error	heredoc_build_delimiter(t_heredoc *state, char **delim);

#endif
