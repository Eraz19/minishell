#ifndef BODY__H
# define BODY__H

# include "lexer.h"
# include "heredoc.h"
# include "context.h"

/** @defgroup heredoc_body Heredoc body
 *  @brief Reads one here-document body from its input up to the delimiter
 *         line and saves it in its backing file (POSIX 2.7.4).
 */

typedef struct s_body
{
	size_t			i;
	t_error			err;
	t_here_mode		mode;
	t_string		input;
	t_string		delim;
	t_string		line;
	bool			is_tty;
	t_string		content;
	t_context_stack	contexts;
}	t_body;

/* ************************************************************************* */
/*                                LIFE_CYCLE                                 */
/* ************************************************************************* */

/**
 * @ingroup heredoc_body
 * @brief Zeroes @p body and initializes its content string and context
 *        stack.
 *
 * @param body Body state initialized by the function (borrowed).
 */
void					body_init(t_body *body);

/**
 * @ingroup heredoc_body
 * @brief Frees the line, content and context stack of @p body, then
 *        zeroes it.
 *
 * @param body Already initialized body state (borrowed).
 */
void					body_free(t_body *body);

t_error					body_load(t_body *body, t_heredoc_read_args *args);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup heredoc_body
 * @brief Builds the lexer configuration of a body scan: expansions
 *        detected, no quoting, heredoc escape rules, end at NUL.
 *
 * @return The scan configuration; the context tag, delimiter lengths and
 *         stack item are left for the lexer entry point to fill in.
 */
t_lexer_context_args	body_context_rules(void);

/* ************************************************************************* */
/*                                INPUT SCAN                                 */
/* ************************************************************************* */

/**
 * @ingroup heredoc_body
 * @brief Handles the input running out before the delimiter line: on a
 *        terminal reads a continuation line and resumes, otherwise (or on
 *        an interactive end of file at the prompt) reports the missing
 *        delimiter.
 *
 * @param body Body state (borrowed).
 * @param continuation Set once a continuation line has been read, so the
 *                     item's saved cursor is rewound only once
 *                     (borrowed).
 * @return @c ERR_REDIRECTION (printed with the delimiter) when the input
 *         ends before the delimiter line: requalified as
 *         @c ERR_POSIX_SYNTAX by the scanner; @c ERR_LIBC (printed) or
 *         @c ERR_INTERNAL (printed) from the continuation reader;
 *         @c ERR_NO on success.
 */
t_error					body_continuation(t_body *body, bool *continuation);

/**
 * @ingroup heredoc_body
 * @brief Accumulates input lines into the body content until the
 *        delimiter line, reading continuation lines as needed.
 *
 * @param body Body state (borrowed).
 * @return @c ERR_REDIRECTION (printed with the delimiter) when the input
 *         ends before the delimiter line; @c ERR_LIBC on allocation
 *         failure or (printed) from the continuation reader;
 *         @c ERR_INTERNAL (printed) from the continuation reader;
 *         @c ERR_NO on success.
 */
t_error					get_body_content(t_body *body);

/**
 * @ingroup heredoc_body
 * @brief Extracts one input line (up to and including @p EOL, or up to
 *        the end of input) into the body's line string and advances
 *        @p i past it.
 *
 * @param body Body state; its line string is initialized by the function
 *             (borrowed).
 * @param EOL Position of the line's newline in the input, NULL when the
 *            input ends without one (borrowed, read-only).
 * @param i Read cursor, advanced past the line (borrowed).
 * @return @c ERR_LIBC on allocation failure, @c ERR_NO on success.
 */
t_error					get_body_line(t_body *body, char *EOL, size_t *i);

/**
 * @ingroup heredoc_body
 * @brief Tells whether the current line is the delimiter line.
 *
 * @warning In @c HEREDOC_MODE_TAB_STRIP the leading tabs are stripped
 *          from the line in place before the comparison: this mutation
 *          is what implements the @c <<- body stripping, since the line
 *          is appended to the content afterwards.
 * @param body Body state (borrowed).
 */
bool					is_line_delimiter(t_body *body);

/* ************************************************************************* */
/*                                LEXER RULES                                */
/* ************************************************************************* */

/**
 * @ingroup heredoc_body
 * @brief Handles a backslash in a body scan: line continuation, and
 *        escapes limited to the POSIX 2.7.4 set (@c $, @c `, @c \).
 *
 * @param lexer Lexer state (borrowed).
 * @return @c ERR_LIBC on allocation failure; @c ERR_UNEXPECTED_EOI
 *         (printed) when the input ends on the escape; @c ERR_NO on
 *         success.
 */
t_error					body_escape(t_lexer *lexer);

/**
 * @ingroup heredoc_body
 * @brief Consumes one plain body character.
 *
 * @param lexer Lexer state (borrowed).
 * @param _ Unused (borrowed, read-only).
 * @return @c ERR_LIBC on allocation failure; @c ERR_UNEXPECTED_EOI
 *         (printed) at end of input; @c ERR_NO on success.
 */
t_error					body_unescape(t_lexer *lexer, void *_);

#endif
