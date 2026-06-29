#ifndef HEREDOC_BODY__H
# define HEREDOC_BODY__H

# include "lexer.h"
# include "heredoc.h"
# include "context.h"

typedef struct s_heredoc_body
{
	size_t					i;
	t_error					err;
	t_heredoc_queue_item	*item;
	t_string				line;
	t_string				content;
	t_context_stack			contexts;
}	t_heredoc_body;

/**
 * @ingroup heredoc
 * @brief Initialises a body state to an empty, ready-to-use value.
 *
 * Zeroes the structure and initialises the content buffer and context stack.
 *
 * @param state Pointer to the body state to initialise (borrowed).
 */
void	heredoc_body_init(t_heredoc_body *state);

/**
 * @ingroup heredoc
 * @brief Releases every resource held by a body state.
 *
 * Frees the content buffer, the context stack, the owned heredoc item (its
 * path and delimiter),
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
 */
void	heredoc_body_load(t_heredoc_body *state, t_heredoc_queue_item *item);

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

t_error	heredoc_body_read(t_heredoc *state, t_heredoc_queue_item *item);

t_lexer_context_args	heredoc_body_context_rules(void);

#endif
