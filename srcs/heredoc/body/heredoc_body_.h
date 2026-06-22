#ifndef HEREDOC_BODY__H
# define HEREDOC_BODY__H

# include "heredoc.h"

/**
 * @ingroup heredoc
 * @struct s_heredoc_body
 * @brief Scratch state for reading and storing one heredoc body.
 *
 * @var s_heredoc_body::i Cursor into the source text; in non-interactive mode
 *                        it borrows the caller's input index, advanced as lines
 *                        are consumed.
 * @var s_heredoc_body::err Last error recorded while reading the body.
 * @var s_heredoc_body::item The heredoc being filled (owned for the body's
 *                           lifetime; released by heredoc_body_free()).
 * @var s_heredoc_body::input Text the body is read from: a deep copy of the
 *                            caller's buffer (non-interactive) or the
 *                            accumulated terminal input (interactive); owned.
 * @var s_heredoc_body::line Current line being examined (owned).
 * @var s_heredoc_body::content Accumulated body bytes to write out (owned).
 */
typedef struct s_heredoc_body
{
	size_t					*i;
	t_error					err;
	t_heredoc_queue_item	*item;
	char					*input;
	char					*line;
	t_buff					content;
}	t_heredoc_body;

/**
 * @ingroup heredoc
 * @brief Initialises a body state to an empty, ready-to-use value.
 *
 * Zeroes the structure and initialises the content buffer.
 *
 * @param state Pointer to the body state to initialise (borrowed).
 */
void	heredoc_body_init(t_heredoc_body *state);

/**
 * @ingroup heredoc
 * @brief Releases every resource held by a body state.
 *
 * Frees the content buffer, the owned heredoc item (its path and delimiter),
 * the input copy and the current line, then resets the structure to zero.
 *
 * @param state Pointer to the body state to free (borrowed).
 */
void	heredoc_body_free(t_heredoc_body *state);

/**
 * @ingroup heredoc
 * @brief Binds a body state to its item and input source.
 *
 * Stores the item and cursor and, in non-interactive mode, takes a deep copy
 * of @p input so the body owns the text it reads.
 *
 * @param state Pointer to the body state (borrowed).
 * @param item Heredoc to fill (ownership held for the body's lifetime).
 * @param input Source text to copy and scan, or NULL for interactive reading.
 * @param i Cursor into @p input (borrowed), advanced as the body is read.
 * @return ERR_NO on success, or ERR_LIBC if the input copy fails.
 */
t_error	heredoc_body_load(t_heredoc_body *state, t_heredoc_queue_item *item,
			char *input, size_t *i);

/**
 * @ingroup heredoc
 * @brief Tests whether the current line is the heredoc delimiter.
 *
 * In TAB_STRIP mode the line's leading tabs are removed first (replacing the
 * stored line), then it is compared against the newline-terminated delimiter
 * for a full-line match.
 *
 * @param state Pointer to the body state (borrowed).
 * @return true if the line is the delimiter (or on allocation failure, with
 *         state->err set), false otherwise.
 */
bool	is_line_delimiter(t_heredoc_body *state);

/**
 * @ingroup heredoc
 * @brief Writes the accumulated body to the heredoc's temporary file.
 *
 * Truncates and opens the item's path, writes the collected content and
 * closes the file.
 *
 * @param state Pointer to the body state (borrowed).
 * @return ERR_NO on success, or ERR_LIBC on open or write failure.
 */
t_error	heredoc_body_save_content(t_heredoc_body *state);

/**
 * @ingroup heredoc
 * @brief Appends the current line to the body content and clears it.
 *
 * Copies the current line into the content buffer, then frees it and sets the
 * line pointer back to NULL.
 *
 * @param state Pointer to the body state (borrowed).
 * @return ERR_NO on success, or ERR_LIBC on allocation failure.
 */
t_error	heredoc_body_line_to_content(t_heredoc_body *state);

/**
 * @ingroup heredoc
 * @brief Extracts the next line (up to and including @p match_EOL) from input.
 *
 * Stores the newline-terminated line in state->line and advances @p i past it.
 *
 * @param state Pointer to the body state (borrowed).
 * @param match_EOL Pointer to the line's terminating newline within the input.
 * @param i In/out cursor into the input, advanced past the extracted line.
 * @return ERR_NO on success, or ERR_LIBC on allocation failure.
 */
t_error	heredoc_body_extract_line(t_heredoc_body *state, char *match_EOL,
			size_t *i);

/**
 * @ingroup heredoc
 * @brief Reads one heredoc's body to completion and stores it.
 *
 * Sets up a private body state, reads lines until the delimiter (interactively
 * when @p input is NULL, otherwise from @p input with @p start advanced),
 * writes the collected body to the heredoc's temporary file, and frees all
 * scratch state including the item. The outcome is mirrored into
 * @p state->err.
 *
 * @param state Pointer to the owning heredoc state (borrowed); receives the
 *              resulting error.
 * @param item Heredoc to fill (consumed: freed by this call).
 * @param input Source text in non-interactive mode (borrowed), or NULL to read
 *              interactively.
 * @param start In/out cursor into @p input, advanced past the consumed body.
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	heredoc_body_store(t_heredoc *state, t_heredoc_queue_item *item,
			char *input, size_t *start);

#endif
