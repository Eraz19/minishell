#ifndef HEREDOC_H
# define HEREDOC_H

# include "error.h"
# include "libft.h"
# include "token.h"
# include "context.h"

/** @defgroup heredoc Heredoc API
 *  @brief Reads and prepares here-documents for the scanner (POSIX 2.7.4).
 *
 *  When the newline ending a command line is reached, the parser asks
 *  the scanner for each pending here-document body in order
 *  (POSIX 2.7.4): the delimiter is quote-removed
 *  (@ref heredoc_expand_delim), the body is read from the current input
 *  up to the delimiter line (@ref heredoc_read_body_from_input,
 *  prompting for continuation lines on a terminal, tab-stripping for
 *  @c <<-) and returned as a string that the parser stores in the syntax
 *  tree. At execution time the redirector expands the stored body
 *  through the expander unless the delimiter was quoted;
 *  @ref heredoc_prepare_for_expansion re-lexes it with the body rules
 *  for that run.
 *
 *  Body semantics follow POSIX 2.7.4: parameter, command and arithmetic
 *  expansion; a backslash escapes only @c $, @c ` and @c \ (a double
 *  quote stays literal); backslash-newline is a line continuation.
 *
 *  ERROR CONTRACT
 *
 *  The module is tokenization-side only: errors stay SPECIFIC, the
 *  callers (scanner endpoint, expander) are the requalifiers. A missing
 *  delimiter (end of input before the delimiter line, including an
 *  interactive end-of-file at the continuation prompt) is printed here
 *  with the delimiter name and reported as @c ERR_NO_DELIM, which the
 *  scanner requalifies as @c ERR_POSIX_SYNTAX. Documented choice: POSIX
 *  2.7.4 says the shell "should, but need not, treat this as a
 *  redirection error" — erroring is the sanctioned strict reading; the
 *  error is detected during token recognition, before any command
 *  exists to attach a redirection failure to, so it is classified as a
 *  syntax error (2.8.1 consequences: diagnostic + non-interactive
 *  exit) rather than as a redirection error.
 *  Delimiter-expansion errors arrive already
 *  qualified and printed by the expander and pass through untouched.
 */

/**
 * @ingroup heredoc
 * @enum e_here_mode
 * @brief Body reading mode of one here-document.
 */
typedef enum e_here_mode
{
	HEREDOC_MODE_NORMAL,	/**< '<<': body kept as read. */
	HEREDOC_MODE_TAB_STRIP	/**< '<<-': leading tabs stripped from body
								 and delimiter lines. */
}	t_here_mode;

/**
 * @ingroup heredoc
 * @struct s_heredoc_read_args
 * @brief Input of one body read.
 *
 * @var s_heredoc_read_args::mode Body reading mode (plain or
 *                                tab-stripping).
 * @var s_heredoc_read_args::input Text the body is read from, @c NULL
 *                                 for an empty input (borrowed,
 *                                 read-only).
 * @var s_heredoc_read_args::start Read cursor into @c input, advanced
 *                                 past the consumed body; @c NULL when
 *                                 no cursor is tracked (borrowed).
 * @var s_heredoc_read_args::delim Quote-removed delimiter with its
 *                                 trailing newline (see
 *                                 @ref heredoc_expand_delim); on the
 *                                 missing-delimiter path its last
 *                                 character is overwritten for the
 *                                 diagnostic (borrowed).
 * @var s_heredoc_read_args::is_tty Tells whether continuation lines can
 *                                  be prompted for.
 */
typedef struct s_heredoc_read_args
{
	t_here_mode 	mode;
	const t_string *input;
	size_t			*start;
	const t_string	*delim;
}	t_heredoc_read_args;

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup heredoc
 * @brief Quote-removes the here-document delimiter (POSIX 2.7.4) and
 *        appends the trailing newline used by the delimiter line
 *        comparison.
 *
 * @param out String receiving the expanded delimiter, initialized by the
 *            function on success (borrowed).
 * @param delim Raw delimiter token (borrowed, read-only).
 * @return From the quote removal, qualified by the expander:
 *         @c ERR_POSIX_EXPANSION (printed), @c ERR_INTERNAL (printed),
 *         @c ERR_LIBC (printed) or @c ERR_INTERRUPTED; @c ERR_LIBC (raw)
 *         if the newline append fails; @c ERR_NO on success.
 */
t_error	heredoc_expand_delim(t_string *out, t_token *delim);

/**
 * @ingroup heredoc
 * @brief Lexes a raw body for expansion: removes escaped newlines from
 *        @p body, then records its @c CONTEXT_HEREDOC context and every
 *        expansion construct into @p out (expander side, raw errors).
 *
 * @param out Destination stack, already initialized by the caller; the
 *            recorded contexts are appended (borrowed).
 * @param body Body text, rewritten without its escaped newlines
 *             (borrowed).
 * @return @c ERR_LIBC on allocation failure; from the scan:
 *         @c ERR_UNEXPECTED_EOI (printed), @c ERR_NO_INPUT_TO_LEX,
 *         @c ERR_NOT_IMPLEMENTED (printed), @c ERR_INCOHERENT_STATE,
 *         @c ERR_EMPTY_STACK, @c ERR_INDEX_OUT_OF_BOUND; @c ERR_NO on
 *         success.
 */
t_error	heredoc_prepare_for_expansion(
			t_context_stack *context_stack_out,
			t_ast_vector *ast_vec_out,
			t_string *body);

/**
 * @ingroup heredoc
 * @brief Reads one here-document body from the input of @p args up to
 *        the delimiter line and returns it; the caller's cursor is
 *        advanced past the consumed body, clamped to the input it
 *        indexes when continuation lines were read.
 *
 * @param out String receiving the body, initialized by the function on
 *            success (borrowed).
 * @param args Input of the read (borrowed).
 * @return Raw errors, requalified by the scanner endpoint:
 *         @c ERR_NO_DELIM (printed with the delimiter) when the input
 *         ends before the delimiter line; @c ERR_LIBC on allocation
 *         failure, or (printed) from the continuation reader;
 *         @c ERR_INTERRUPTED and @c ERR_INTERNAL (printed) from the
 *         continuation reader; @c ERR_NO on success.
 */
t_error	heredoc_read_body_from_input(t_string *out, t_heredoc_read_args *args);

#endif
