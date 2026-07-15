#ifndef HEREDOC_H
# define HEREDOC_H

# include "error.h"
# include "libft.h"
# include "token.h"
# include "context.h"

/** @defgroup heredoc Heredoc API
 *  @brief Collects, reads and expands here-documents (POSIX 2.7.4).
 *
 *  The parser reports each here-document operator through the scanner
 *  (@ref heredoc_register): the delimiter is quote-removed and a backing
 *  temporary file is created. Once a complete command line is parsed, the
 *  scanner drains the queue (@ref heredoc_read_body_from_input): each body
 *  is read from the current input (prompting for continuation lines on a
 *  terminal) up to its delimiter line, tab-stripped for @c <<-, and saved
 *  in its backing file. At execution time the redirector expands the body
 *  in place (@ref heredoc_expand_body) unless the delimiter was quoted.
 *
 *  Body semantics follow POSIX 2.7.4: parameter, command and arithmetic
 *  expansion; a backslash escapes only @c $, @c ` and @c \ (a double
 *  quote stays literal); backslash-newline is a line continuation.
 *
 *  ERROR CONTRACT
 *
 *  The module has two API surfaces with different qualification rules:
 *
 *  - Tokenization side (@ref heredoc_register,
 *    @ref heredoc_read_body_from_input, @ref heredoc_prepare_for_expansion):
 *    errors stay SPECIFIC, the callers (scanner endpoints, expander) are
 *    the requalifiers. A missing delimiter (end of input before the
 *    delimiter line, including an interactive end-of-file at the
 *    continuation prompt) is printed here with the delimiter name and
 *    reported as @c ERR_REDIRECTION, which the scanner requalifies as
 *    @c ERR_POSIX_SYNTAX.
 *  - Execution side (@ref heredoc_expand_body, @ref heredoc_load): the
 *    callers no longer need specifics, so these endpoints requalify
 *    through @c heredoc_error_qualify (see heredoc_.h): expansion
 *    failures become @c ERR_POSIX_EXPANSION, temp-file write failures
 *    @c ERR_REDIRECTION (further requalified by the executor),
 *    inconsistencies @c ERR_INTERNAL, all printed at requalification.
 *
 *  File diagnostics are printed at the most specific point, with the
 *  backing file path.
 *
 *  @warning The backing files (@c /tmp/minishell_heredoc_N) are never
 *           unlinked: neither after execution nor on a registration that
 *           fails after creating the file. A cleanup design is pending.
 *
 *  Expansion errors arrive already qualified and printed by the expander
 *  (@c ERR_POSIX_EXPANSION, @c ERR_POSIX_ASSIGNMENT, @c ERR_INTERNAL,
 *  @c ERR_LIBC): the scanner lets them through untouched.
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

typedef struct s_heredoc_read_args
{
	t_here_mode 	mode;
	const t_string *input;
	size_t			*start;
	const t_string	*delim;
	bool			is_tty;
}	t_heredoc_read_args;

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

t_error	heredoc_expand_delim(t_string *out, const t_token *delim);

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
t_error	heredoc_prepare_for_expansion(t_context_stack *out, t_string *body);

t_error	heredoc_read_body_from_input(t_string *out, t_heredoc_read_args *args);

#endif
