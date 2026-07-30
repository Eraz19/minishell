#ifndef TOKEN_RECOGNITION_CONTEXT_H
# define TOKEN_RECOGNITION_CONTEXT_H

# include "lexer.h"

/* ************************************************************************* */
/*                                  TYPES                                    */
/* ************************************************************************* */

/**
 * @ingroup lexer
 * @struct s_token_recognition_escape
 * @brief Per-construct rules applied to a @c \\ while scanning a context.
 *
 * @var s_token_recognition_escape::lexer Lexer being driven (borrowed).
 * @var s_token_recognition_escape::line_continuation True when the
 *      construct removes @c \\<newline> pairs (POSIX 2.2.1); false where
 *      the pair stays literal (@c '...', @c $'...', plain @c `...`).
 * @var s_token_recognition_escape::is_in_whitelist Predicate deciding
 *      whether the escaped character is consumed with the @c \\ .
 * @var s_token_recognition_escape::is_in_special_whitelist Replacement
 *      whitelist used while @c is_in_special_context holds.
 * @var s_token_recognition_escape::is_in_special_context Optional
 *      predicate switching to the special whitelist (e.g. a backtick
 *      surrounded by double quotes); NULL when the construct has none.
 */
typedef struct s_token_recognition_escape
{
	t_lexer	*lexer;
	bool	line_continuation;
	bool	(*is_in_whitelist)(char);
	bool	(*is_in_special_whitelist)(char);
	bool	(*is_in_special_context)(t_lexer *);
}	t_token_recognition_escape;

/**
 * @ingroup lexer
 * @struct s_token_recognition_unescape
 * @brief Per-construct rules applied to a plain (unescaped) character
 *        while scanning a context.
 *
 * @var s_token_recognition_unescape::lexer Lexer being driven (borrowed).
 * @var s_token_recognition_unescape::special_args Opaque argument
 *      forwarded to @c special_handler (borrowed).
 * @var s_token_recognition_unescape::special_handler Optional override
 *      consuming the current character (e.g. arithmetic parenthesis
 *      tracking); NULL to consume it verbatim.
 */
typedef struct s_token_recognition_unescape
{
	t_lexer	*lexer;
	void	*special_args;
	t_error	(*special_handler)(t_lexer *, void *);
}	t_token_recognition_unescape;

/**
 * @ingroup lexer
 * @struct s_token_recognition_context
 * @brief Full rule set describing how to scan one quoting or expansion
 *        construct, consumed by @ref scan_context.
 *
 * @var s_token_recognition_context::lexer Lexer being driven (borrowed).
 * @var s_token_recognition_context::opening_len Length of the opening
 *      delimiter to consume before scanning the body.
 * @var s_token_recognition_context::closing_len Length of the closing
 *      delimiter to consume when @c is_end matches.
 * @var s_token_recognition_context::context_item Context-stack item
 *      recording the @c [start, @c end) span of the construct inside the
 *      token value (borrowed); may be NULL — the span is then not
 *      recorded (@ref scan_context_start and @ref scan_context_end both
 *      guard it).
 * @var s_token_recognition_context::unescaped_args Opaque argument passed
 *      to @c is_end and @c unescaped (borrowed).
 * @var s_token_recognition_context::escape Hook run on @c \\ .
 * @var s_token_recognition_context::is_end Predicate detecting the closing
 *      character of the construct.
 * @var s_token_recognition_context::unescaped Hook consuming a plain
 *      character.
 * @var s_token_recognition_context::quoting Optional hook scanning a
 *      nested quoting construct; NULL when the construct allows none.
 * @var s_token_recognition_context::is_quoting Predicate detecting a
 *      nested quoting construct opening; only read when @c quoting is set.
 * @var s_token_recognition_context::expansion Optional hook scanning a
 *      nested expansion construct; NULL when the construct allows none.
 * @var s_token_recognition_context::is_expansion Predicate detecting a
 *      nested expansion construct opening; only read when @c expansion is
 *      set.
 */
typedef struct s_token_recognition_context
{
	t_lexer					*lexer;
	size_t					opening_len;
	size_t					closing_len;
	t_context_stack_item	*context_item;
	void					*unescaped_args;
	t_error					(*escape)(t_lexer *);
	bool					(*is_end)(char, void *);
	t_error					(*unescaped)(t_lexer *, void *);
	t_error					(*quoting)(t_lexer *, t_context);
	bool					(*is_quoting)(char *, t_context *);
	t_error					(*expansion)(t_lexer *, t_context);
	bool					(*is_expansion)(char *, t_context *);
}	t_token_recognition_context;

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup lexer
 * @brief Dispatches @p context to the matching @c scan_*_context function.
 *
 * @warning Only quoting and expansion contexts are accepted;
 *          @c CONTEXT_NONE and @c CONTEXT_HEREDOC are asserted out.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @param context Construct opening at the cursor.
 * @return @c ERR_NO on success; @c ERR_LIBC, @c ERR_POSIX_SYNTAX
 *         (printed) or @c ERR_VEOF on module-produced failure, with
 *         module-external errors bubbling through unlisted;
 *         @c ERR_CTX_END_NOT_FOUND when a @c CONTEXT_ARITH scan finds no
 *         closing @c ) .
 */
t_error	token_recognition_consume_context(t_lexer *lexer, t_context context);

/* ************************************************************************* */
/*                                  ARITH                                    */
/* ************************************************************************* */

/**
 * @ingroup lexer
 * @brief Escape rules of @c $((...)): consume the @c \\ and the next
 *        character when it belongs to the double-quote whitelist.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @return @c ERR_NO on success, @c ERR_LIBC on allocation failure; at end
 *         of input the continuation set of @ref on_context_scan_EOI
 *         (@c ERR_POSIX_SYNTAX printed, @c ERR_VEOF, @c ERR_LIBC), with
 *         module-external errors bubbling through unlisted.
 */
t_error	arith_context_escape_rules(t_lexer *lexer);

/**
 * @ingroup lexer
 * @brief Unescaped-character rules of @c $((...)): consume the character
 *        while tracking parenthesis nesting.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @param nesting_depth In/out parenthesis depth, as a @c size_t pointer
 *        (borrowed).
 * @return @c ERR_NO on success, @c ERR_LIBC on allocation failure; at end
 *         of input the same continuation set as
 *         @ref arith_context_escape_rules.
 */
t_error	arith_context_unescape_rules(t_lexer *lexer, void *nesting_depth);

/**
 * @ingroup lexer
 * @brief Scans a @c $((...)) construct into the current token, restoring
 *        the pre-scan state when no matching @c ) closes it.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @return @c ERR_NO on success; @c ERR_CTX_END_NOT_FOUND when the
 *         construct does not close as arithmetic (the caller rescans it as
 *         command substitution); otherwise the same failure set as
 *         @ref token_recognition_consume_context.
 */
t_error	scan_arith_context(t_lexer *lexer);

/* ************************************************************************* */
/*                                BACKTICK                                   */
/* ************************************************************************* */

/**
 * @ingroup lexer
 * @brief Escape rules of @c `...`: consume the @c \\ and the next
 *        character when whitelisted, switching to a special whitelist when
 *        the backtick is surrounded by double quotes or arithmetic.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @return Same set as @ref arith_context_escape_rules.
 */
t_error	backtick_context_escape_rules(t_lexer *lexer);

/**
 * @ingroup lexer
 * @brief Unescaped-character rules of @c `...`: consume the character
 *        verbatim.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @param _ Unused.
 * @return Same set as @ref arith_context_unescape_rules.
 */
t_error	backtick_context_unescape_rules(t_lexer *lexer, void *_);

/**
 * @ingroup lexer
 * @brief Scans a @c `...` construct into the current token, allowing
 *        nested quoting and expansion constructs.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @return @c ERR_NO on success; otherwise the same failure set as
 *         @ref token_recognition_consume_context.
 */
t_error	scan_backtick_context(t_lexer *lexer);

/* ************************************************************************* */
/*                                 CMD_SUB                                   */
/* ************************************************************************* */

/**
 * @ingroup lexer
 * @brief Scans a @c $(...) construct by parsing the embedded command with
 *        a child parser, storing its AST on the token and consuming the
 *        construct text up to the closing @c ) .
 *
 * @param lexer Already initialized lexer (borrowed).
 * @return @c ERR_NO on success; @c ERR_LIBC (token growth) on
 *         module-produced failure — every other failure arrives from the
 *         embedded command-substitution parse (cmd_sub module, context
 *         stack) and bubbles through unlisted.
 */
t_error	scan_cmd_sub_context(t_lexer *lexer);

/* ************************************************************************* */
/*                              DOLLAR_SQUOTE                                */
/* ************************************************************************* */

/**
 * @ingroup lexer
 * @brief Escape rules of @c $'...': consume the @c \\ and the next
 *        character when it belongs to the @c $'...' whitelist.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @return Same set as @ref arith_context_escape_rules.
 */
t_error	dollar_squote_context_escape_rules(t_lexer *lexer);

/**
 * @ingroup lexer
 * @brief Unescaped-character rules of @c $'...': consume the character
 *        verbatim.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @param _ Unused.
 * @return Same set as @ref arith_context_unescape_rules.
 */
t_error	dollar_squote_context_unescape_rules(t_lexer *lexer, void *_);

/**
 * @ingroup lexer
 * @brief Scans a @c $'...' construct into the current token; no nested
 *        construct is recognized.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @return @c ERR_NO on success; otherwise the same failure set as
 *         @ref token_recognition_consume_context.
 */
t_error	scan_dollar_squote_context(t_lexer *lexer);

/* ************************************************************************* */
/*                                  DQUOTE                                   */
/* ************************************************************************* */

/**
 * @ingroup lexer
 * @brief Escape rules of @c "...": consume the @c \\ and the next
 *        character when it belongs to the double-quote whitelist
 *        (POSIX 2.2.3).
 *
 * @param lexer Already initialized lexer (borrowed).
 * @return Same set as @ref arith_context_escape_rules.
 */
t_error	dquote_context_escape_rules(t_lexer *lexer);

/**
 * @ingroup lexer
 * @brief Unescaped-character rules of @c "...": consume the character
 *        verbatim.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @param _ Unused.
 * @return Same set as @ref arith_context_unescape_rules.
 */
t_error	dquote_context_unescape_rules(t_lexer *lexer, void *_);

/**
 * @ingroup lexer
 * @brief Scans a @c "..." construct into the current token, allowing
 *        nested expansion constructs.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @return @c ERR_NO on success; otherwise the same failure set as
 *         @ref token_recognition_consume_context.
 */
t_error	scan_dquote_context(t_lexer *lexer);

/* ************************************************************************* */
/*                                   NONE                                    */
/* ************************************************************************* */

t_error	none_context_escape_rules(t_lexer *lexer);

t_error	none_context_unescape_rules(t_lexer *lexer, void *_);

t_error	scan_none_context(t_lexer *lexer);

/* ************************************************************************* */
/*                                  PARAM                                    */
/* ************************************************************************* */

/**
 * @ingroup lexer
 * @brief Escape rules of @c ${...}: consume the @c \\ and the next
 *        character when it belongs to the parameter whitelist.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @return Same set as @ref arith_context_escape_rules.
 */
t_error	param_context_escape_rules(t_lexer *lexer);

/**
 * @ingroup lexer
 * @brief Unescaped-character rules of @c ${...}: consume the character
 *        verbatim.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @param _ Unused.
 * @return Same set as @ref arith_context_unescape_rules.
 */
t_error	param_context_unescape_rules(t_lexer *lexer, void *_);

/**
 * @ingroup lexer
 * @brief Scans a @c ${...} construct into the current token, allowing
 *        nested quoting and expansion constructs.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @return @c ERR_NO on success; otherwise the same failure set as
 *         @ref token_recognition_consume_context.
 */
t_error	scan_param_context(t_lexer *lexer);

/* ************************************************************************* */
/*                                  SQUOTE                                   */
/* ************************************************************************* */

/**
 * @ingroup lexer
 * @brief Escape rules of @c '...': consume the @c \\ and the next
 *        character when it belongs to the single-quote whitelist
 *        (POSIX 2.2.1 keeps everything literal).
 *
 * @param lexer Already initialized lexer (borrowed).
 * @return Same set as @ref arith_context_escape_rules.
 */
t_error	squote_context_escape_rules(t_lexer *lexer);

/**
 * @ingroup lexer
 * @brief Unescaped-character rules of @c '...': consume the character
 *        verbatim.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @param _ Unused.
 * @return Same set as @ref arith_context_unescape_rules.
 */
t_error	squote_context_unescape_rules(t_lexer *lexer, void *_);

/**
 * @ingroup lexer
 * @brief Scans a @c '...' construct into the current token; no nested
 *        construct is recognized.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @return @c ERR_NO on success; otherwise the same failure set as
 *         @ref token_recognition_consume_context.
 */
t_error	scan_squote_context(t_lexer *lexer);

#endif
