#ifndef HEREDOC_H
# define HEREDOC_H

# include "error.h"
# include "libft.h"
# include "token.h"

/** @defgroup heredoc Heredoc API
 *  @brief POSIX here-documents collected into owned temporary files.
 *
 *  Each `<<` / `<<-` redirection is registered as a pending heredoc, then its
 *  body is read line by line until the delimiter and spilled to a private
 *  temporary file. The module keeps full ownership of its data: the delimiter
 *  handed in is deep copied (the caller keeps its buffer) and the scanned
 *  input is deep copied before use, so no buffer is shared across the
 *  boundary. The single thing handed out is the temporary file path, a deep
 *  copy the caller takes ownership of (the caller is also responsible for
 *  unlinking the file once the command has consumed it). Temporary file names
 *  are made unique with a monotonic per-state counter combined with O_EXCL, so
 *  several heredocs queued in the same instant never clash.
 */

typedef t_vector	t_heredoc_queue;

/**
 * @ingroup heredoc
 * @enum e_heredoc_mode
 * @brief Selects how body lines and the delimiter are matched.
 *
 * @var e_heredoc_mode::NORMAL Plain `<<`: lines are kept verbatim.
 * @var e_heredoc_mode::TAB_STRIP `<<-`: leading tab characters are stripped
 *                                from every body line and from the delimiter
 *                                comparison.
 */
typedef enum e_heredoc_mode
{
	HEREDOC_MODE_NORMAL,
	HEREDOC_MODE_TAB_STRIP
}	t_heredoc_mode;

/**
 * @ingroup heredoc
 * @struct s_heredoc_queue_item
 * @brief One pending heredoc awaiting its body.
 *
 * @var s_heredoc_queue_item::mode Verbatim or tab-stripping behaviour.
 * @var s_heredoc_queue_item::path Temporary file the body is written to
 *                                 (owned; freed with the item).
 * @var s_heredoc_queue_item::delim Delimiter to stop at (owned), stored after
 *                                  quote removal and terminated by a newline so
 *                                  it matches a whole body line exactly.
 */
typedef struct s_heredoc_queue_item
{
	size_t			*i;
	t_heredoc_mode	mode;
	char			*path;
	bool			is_tty;
	char			*delim;
	char			*input;
}	t_heredoc_queue_item;

typedef struct s_heredoc
{
	t_error			err;
	t_heredoc_queue	queue;
	int				file_id;
}	t_heredoc;

/**
 * @ingroup heredoc
 * @brief Initialises a heredoc state to an empty, ready-to-use value.
 *
 * Zeroes the structure, initialises the pending-heredoc queue and seeds the
 * temporary-file counter from the current time so distinct shell runs start
 * from different names.
 *
 * @param state Pointer to the heredoc state to initialise (borrowed).
 */
void	heredoc_init(t_heredoc *state);

/**
 * @ingroup heredoc
 * @brief Releases every resource held by a heredoc state.
 *
 * Frees the queue together with each item's path and delimiter, then resets
 * the structure to zero. The temporary files themselves are not unlinked here;
 * that is the responsibility of whoever consumed the handed-out paths.
 *
 * @param state Pointer to the heredoc state to free (borrowed).
 */
void	heredoc_free(t_heredoc *state);

t_error	heredoc_store_all(char *input, size_t *start);

t_error	heredoc_add_to_queue(
			t_string *path,
			t_token *delim,
			t_heredoc_mode mode,
			bool is_tty);

#endif
