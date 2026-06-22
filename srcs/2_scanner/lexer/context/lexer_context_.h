#ifndef LEXER_CONTEXT__H
# define LEXER_CONTEXT__H

# include "lexer_.h"

/**
 * @ingroup scanner
 * @struct s_escape_args
 * @brief Configures how a backslash is handled inside a given context.
 *
 * @var s_escape_args::enable_line_continuation Whether "\\<newline>" is a line
 *                                              continuation (removed) here.
 * @var s_escape_args::is_in_whitelist Characters that keep their special
 *                                     meaning after a backslash (normal case).
 * @var s_escape_args::is_in_special_whitelist Same, but when wrapped in a
 *                                             special surrounding context.
 * @var s_escape_args::is_in_special_context Predicate detecting that special
 *                                           surrounding context (may be NULL).
 */
typedef struct s_escape_args
{
	bool	enable_line_continuation;
	bool	(*is_in_whitelist)(char);
	bool	(*is_in_special_whitelist)(char);
	bool	(*is_in_special_context)(t_lexer *);
}	t_escape_args;

/**
 * @ingroup scanner
 * @struct s_unescape_args
 * @brief Configures how a plain (non-delimiter) character is consumed.
 *
 * @var s_unescape_args::special_args Opaque state passed to the handler (e.g.
 *                                    the arithmetic nesting depth).
 * @var s_unescape_args::special_handler Optional per-character handler; when
 *                                       NULL the character is consumed as-is.
 */
typedef struct s_unescape_args
{
	void	*special_args;
	t_error	(*special_handler)(t_lexer *, void *);
}	t_unescape_args;

/**
 * @ingroup scanner
 * @struct s_context_args
 * @brief Full configuration of one context scan driven by lexer_context_scan.
 *
 * @var s_context_args::context The context tag pushed while scanning.
 * @var s_context_args::opening_len Length of the opening delimiter to consume.
 * @var s_context_args::closing_len Length of the closing delimiter to consume.
 * @var s_context_args::stack_item Item whose [start, end) span this scan fills
 *                                 in: start when the context opens, end when it
 *                                 closes (NULL to record no span).
 * @var s_context_args::unescaped_args Opaque state for the unescaped handler.
 * @var s_context_args::escape Backslash handler.
 * @var s_context_args::is_end Predicate detecting the closing delimiter.
 * @var s_context_args::unescaped Plain-character handler.
 * @var s_context_args::quoting Nested quoting handler (may be NULL).
 * @var s_context_args::is_quoting Nested quoting detector (may be NULL).
 * @var s_context_args::expansion Nested expansion handler (may be NULL).
 * @var s_context_args::is_expansion Nested expansion detector (may be NULL).
 */
typedef struct s_context_args
{
	t_context				context;
	size_t					opening_len;
	size_t					closing_len;
	t_context_parser_stack_item	*stack_item;
	void					*unescaped_args;
	t_error					(*escape)(t_lexer *);
	bool					(*is_end)(char, void *);
	t_error					(*unescaped)(t_lexer *, void *);
	t_error					(*quoting)(t_lexer *, t_context);
	bool					(*is_quoting)(char *, t_context *);
	t_error					(*expansion)(t_lexer *, t_context);
	bool					(*is_expansion)(char *, t_context *);
}	t_context_args;

/**
 * @ingroup scanner
 * @brief Handles reaching end-of-input while still inside a context.
 *
 * When streaming from stdin, reads a continuation line and resumes; otherwise
 * reports an unterminated-construct error.
 *
 * @param state Pointer to the lexer state (borrowed).
 * @return ERR_NO once more input is available, or ERR_UNEXPECTED_EOI.
 */
t_error	context_EOI(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Consumes the character following a backslash when whitelisted.
 *
 * Uses the special or normal whitelist depending on the surrounding context;
 * a non-whitelisted character is left for normal processing.
 *
 * @param state Pointer to the lexer state (borrowed).
 * @param args Escape configuration for the current context.
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	context_escape_next_char(t_lexer *state, t_escape_args args);

/**
 * @ingroup scanner
 * @brief Generic scan loop for one quoting/expansion context.
 *
 * Pushes the context, consumes the opening delimiter, then loops handling the
 * closing delimiter, backslashes, nested quoting/expansion and plain
 * characters; on the closing delimiter it consumes it and pops the context.
 *
 * @param state Pointer to the lexer state (borrowed).
 * @param args Configuration describing this context.
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	lexer_context_scan(t_lexer *state, t_context_args args);

/**
 * @ingroup scanner
 * @brief Handles a backslash inside a context (line continuation or escape).
 * @param state Pointer to the lexer state (borrowed).
 * @param args Escape configuration for the current context.
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	lexer_context_escape(t_lexer *state, t_escape_args args);

/**
 * @ingroup scanner
 * @brief Consumes one plain character of a context (or end-of-input/handler).
 * @param state Pointer to the lexer state (borrowed).
 * @param args Unescaped-character configuration for the current context.
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	lexer_context_unescape(t_lexer *state, t_unescape_args args);

/**
 * @ingroup scanner
 * @brief Scans a parameter expansion: ${...}.
 * @param state Pointer to the lexer state (borrowed).
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	lexer_context_param(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Scans an arithmetic expansion: $((...)).
 *
 * Tracks parenthesis nesting and, when the trailing ")" is missing, rolls back
 * so the caller can retry the construct as a command substitution.
 *
 * @param state Pointer to the lexer state (borrowed).
 * @return ERR_NO on success, ERR_CTX_END_NOT_FOUND when it is not arithmetic.
 */
t_error	lexer_context_arith(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Scans a double-quoted section: "..." (expansions stay active).
 * @param state Pointer to the lexer state (borrowed).
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	lexer_context_dquote(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Scans a backquote command substitution: `...`.
 * @param state Pointer to the lexer state (borrowed).
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	lexer_context_backtick(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Scans a single-quoted section: '...' (everything literal).
 * @param state Pointer to the lexer state (borrowed).
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	lexer_context_squote(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Scans an ANSI-C quoted section: $'...'.
 * @param state Pointer to the lexer state (borrowed).
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	lexer_context_dollar_squote(t_lexer *state);

#endif
