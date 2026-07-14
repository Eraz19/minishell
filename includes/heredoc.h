#ifndef HEREDOC_H
# define HEREDOC_H

# include "error.h"
# include "libft.h"
# include "token.h"

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
 * @typedef t_heredoc_queue
 * @brief Pending here-documents in parsing order, backed by a
 *        @ref t_vector of @ref s_heredoc_item values (owned by the queue).
 */
typedef t_vector	t_heredoc_queue;

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
 * @struct s_heredoc_item
 * @brief One registered here-document waiting for its body.
 *
 * @var s_heredoc_item::i Read cursor into s_heredoc_item::input; advanced
 *                        past the delimiter line once the body is consumed
 *                        (owned value, seeded from the caller's cursor and
 *                        handed back through the API on success).
 * @var s_heredoc_item::mode Body reading mode (@c << or @c <<-).
 * @var s_heredoc_item::path Backing temporary file path, a @ref t_string
 *                           owned by the item.
 * @var s_heredoc_item::delim Quote-removed, newline-terminated delimiter,
 *                            a @ref t_string owned by the item.
 * @var s_heredoc_item::input Copy of the input text the body is read
 *                            from, a @ref t_string owned by the item.
 * @var s_heredoc_item::is_tty Whether continuation lines may be prompted
 *                             for on a terminal.
 */
typedef struct s_heredoc_item
{
	size_t		i;
	t_here_mode	mode;
	t_string	path;
	t_string	delim;
	t_string	input;
	bool		is_tty;
}	t_heredoc_item;

/**
 * @ingroup heredoc
 * @struct s_heredoc
 * @brief Aggregate state of the heredoc module.
 *
 * @var s_heredoc::err Last error recorded by the module.
 * @var s_heredoc::queue Pending here-documents, managed by the
 *                       heredoc_queue submodule.
 * @var s_heredoc::is_tty Whether the shell input is an interactive
 *                        terminal, derived from the input mode at load.
 * @var s_heredoc::file_id Identifier of the last backing file created,
 *                         @c -1 before the first one.
 */
typedef struct s_heredoc
{
	t_error			err;
	t_heredoc_queue	queue;
	bool			is_tty;
	int				file_id;
}	t_heredoc;

/* ************************************************************************* */
/*                                LIFE_CYCLE                                 */
/* ************************************************************************* */

/**
 * @ingroup heredoc
 * @brief Zeroes @p heredoc, initializes its empty queue and resets the
 *        backing file identifier.
 *
 * @param heredoc Heredoc state initialized by the function (borrowed).
 */
void	heredoc_init(t_heredoc *heredoc);

/**
 * @ingroup heredoc
 * @brief Derives the terminal mode of @p heredoc from the shell
 *        invocation options.
 *
 * @param heredoc Already initialized heredoc state (borrowed).
 * @return @c ERR_INTERNAL (printed) if the shell parameters are
 *         unavailable, @c ERR_NO on success.
 */
t_error	heredoc_load(t_heredoc *heredoc);

/**
 * @ingroup heredoc
 * @brief Frees the queue of @p heredoc and zeroes it.
 *
 * @param heredoc Already initialized heredoc state (borrowed).
 */
void	heredoc_free(t_heredoc *heredoc);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup heredoc
 * @brief Expands a here-document body: applies the POSIX 2.7.4 set
 *        (parameter, command and arithmetic expansion, quote removal,
 *        here-document lexing rules) to @p in through @c expand_str
 *        (execution side, qualified).
 *
 * @param out String receiving the expanded body, initialized by the
 *            function (borrowed).
 * @param in Body text to expand (borrowed, read-only).
 * @param exit_status Destination for the exit status of the last command
 *                    substitution; unused until command substitution is
 *                    implemented (borrowed).
 * @return @c ERR_POSIX_EXPANSION (printed) on a user-facing expansion
 *         failure; @c ERR_POSIX_ASSIGNMENT (printed) on a readonly
 *         assignment; @c ERR_INTERRUPTED when a signal interrupts the
 *         work; @c ERR_LIBC (printed) on system failure; @c ERR_INTERNAL
 *         (printed) on internal inconsistency; @c ERR_NO on success.
 */
t_error	heredoc_expand_body(
			t_string *out,
			const t_string *in,
			int *exit_status);

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
			t_context_stack *out,
			t_string *body);

/**
 * @ingroup heredoc
 * @brief Reads every pending here-document body from @p input (prompting
 *        for continuation lines on a terminal), saving each body in its
 *        backing file (tokenization side, raw errors).
 *
 * @param input Input text holding the bodies, NULL to read them from
 *              prompted lines only (borrowed, read-only).
 * @param start Read cursor into @p input, NULL or out of range to start
 *              from the beginning; advanced past each consumed body and
 *              delimiter line on success, so tokenization resumes after
 *              the here-document (borrowed, only dereferenced during the
 *              call — never stored).
 * @return @c ERR_REDIRECTION (printed with the delimiter) when the input
 *         ends before a delimiter line, including an interactive end of
 *         file at the continuation prompt: requalified as
 *         @c ERR_POSIX_SYNTAX by the scanner; @c ERR_POSIX_WRITE (printed
 *         with the path) on a backing file write failure;
 *         @c ERR_INTERRUPTED when a signal interrupts a file operation;
 *         @c ERR_LIBC (printed for file failures) on system failure;
 *         @c ERR_INTERNAL (printed) from the continuation reader;
 *         @c ERR_SHELL_NOT_FOUND if the shell data is unavailable;
 *         @c ERR_NO on success.
 */
t_error	heredoc_read_body_from_input(const t_string *input, size_t *start);

/**
 * @ingroup heredoc
 * @brief Registers a here-document reported by the parser: creates its
 *        backing file, quote-removes its delimiter and queues it for
 *        @ref heredoc_read_body_from_input (tokenization side, raw
 *        errors).
 *
 * @param out String receiving the backing file path, initialized by the
 *            function and freed on failure (borrowed).
 * @param delim Raw delimiter token (borrowed, read-only).
 * @param mode Body reading mode (@c << or @c <<-).
 * @return @c ERR_HEREDOC_MAX_ID_REACHED (printed) when no backing file
 *         name is available; @c ERR_EXP_RESULT_INCOHERENT if the
 *         delimiter does not quote-remove to exactly one field;
 *         @c ERR_INTERRUPTED when a signal interrupts the file creation;
 *         @c ERR_LIBC (printed) on system failure;
 *         @c ERR_SHELL_NOT_FOUND if the shell data is unavailable;
 *         @c ERR_POSIX_EXPANSION or @c ERR_INTERNAL (printed, qualified
 *         by the expander) if the delimiter's quote removal fails;
 *         @c ERR_NO on success.
 */
t_error	heredoc_register(t_string *out, const t_token *delim, t_here_mode mode);

#endif
