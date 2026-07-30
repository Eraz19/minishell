#ifndef HEREDOC_BODY_H
# define HEREDOC_BODY_H

# include "lexer.h"
# include "heredoc.h"

/* ************************************************************************* */
/*                                  TYPES                                    */
/* ************************************************************************* */

/**
 * @ingroup heredoc
 * @struct s_body
 * @brief Working state of one here-document body read.
 *
 * @var s_body::i Offset of the next unread character in @c input.
 * @var s_body::err Last error recorded by a body operation.
 * @var s_body::mode Body treatment (@ref t_here_mode).
 * @var s_body::line Physical line under examination (owned).
 * @var s_body::input Private copy of the lexer input text, grown by PS2
 *      continuation reads (owned).
 * @var s_body::delim Expanded delimiter, newline-terminated so it compares
 *      equal to a whole physical line (owned).
 * @var s_body::content Accumulated body lines (owned).
 */
typedef struct s_body
{
	size_t			i;
	t_error			err;
	t_here_mode		mode;
	t_string		line;
	t_string		input;
	t_string		delim;
	t_string		content;
}	t_body;

/* ************************************************************************* */
/*                                LIFE_CYCLE                                 */
/* ************************************************************************* */

/**
 * @ingroup heredoc
 * @brief Zeroes @p body and initializes its content as an empty string.
 *
 * @param body Body state to initialize; initialized by the function
 *             (borrowed).
 */
void	body_init(t_body *body);

/**
 * @ingroup heredoc
 * @brief Fills @p body from the lexer state: copies the current input text
 *        (empty when the lexer has none) and its cursor, selects the strip
 *        mode and builds the expanded delimiter.
 *
 * @param body Already initialized body state (borrowed).
 * @param lexer Lexer whose current input is copied (borrowed, read-only).
 * @param delim Delimiter word token (borrowed, read-only).
 * @param strip True for @c <<- tab stripping.
 * @return @c ERR_NO on success; @c ERR_LIBC (module allocation failure)
 *         on module-produced failure. Module-external errors (delimiter
 *         expansion by the expander) bubble through unlisted.
 */
t_error	body_load(t_body *body, t_lexer *lexer, t_token *delim, bool strip);

/**
 * @ingroup heredoc
 * @brief Frees every owned string of @p body and resets its scalar state.
 *
 * @param body Already initialized body state (borrowed).
 */
void	body_free(t_body *body);

/* ************************************************************************* */
/*                                   OPS                                     */
/* ************************************************************************* */

t_error	scan_heredoc_body_context(t_scanner *scanner, t_token *out);

/**
 * @ingroup heredoc
 * @brief Consumes physical lines from @c body->input (reading PS2
 *        continuations when exhausted) until the delimiter line,
 *        accumulating them into @c body->content; in
 *        @c HEREDOC_MODE_TAB_STRIP each line loses its leading tabs before
 *        the delimiter comparison. The delimiter line is consumed but not
 *        appended.
 *
 * @param body Loaded body state (see @ref body_load) (borrowed).
 * @return @c ERR_NO on success; @c ERR_NO_DELIM (printed, no more input
 *         before the delimiter — both end-of-continuation reports of the
 *         PS2 read, @c ERR_VEOF interactive and @c ERR_POSIX_SYNTAX
 *         non-interactive, are converted at production by
 *         @ref error_missing_delimiter) or
 *         @c ERR_LIBC (module allocation failure) on module-produced
 *         failure. Module-external errors (params, sig on the PS2 read)
 *         bubble through unlisted.
 */
t_error	scan_input_for_heredoc_body(t_body *body);

#endif
