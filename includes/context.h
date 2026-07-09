#ifndef CONTEXT_H
# define CONTEXT_H

# include "error.h"
# include "libft.h"

/** @defgroup context Context API
 *  @brief Tracks the lexical context (quoting, substitution) of shell input.
 *
 *  A context describes which POSIX construct the lexer is currently inside
 *  (quotes, command substitution, arithmetic expansion, ...). Contexts nest,
 *  so they are recorded on a stack of @ref t_context_stack_item entries.
 *  The module also provides the per-context predicates the lexer uses as
 *  callbacks: start detectors (@c is_context_*_start), escape whitelists
 *  (@c is_in_context_*_whitelist) and ending detectors
 *  (@c is_context_*_ending).
 */

/**
 * @typedef t_context_stack
 * @brief Stack of nested contexts, backed by a @ref t_vector of
 *        @ref t_context_stack_item pointers (owned by the stack).
 */
typedef t_vector	t_context_stack;

/**
 * @enum e_context
 * @brief Lexical context a piece of shell input belongs to.
 */
typedef enum e_context
{
	CONTEXT_NONE,
	CONTEXT_SQUOTE,
	CONTEXT_DQUOTE,
	CONTEXT_DOLLAR_SQUOTE,
	CONTEXT_BACKTICK,
	CONTEXT_CMD_SUB,
	CONTEXT_ARITH,
	CONTEXT_PARAM,
	CONTEXT_HEREDOC,
}	t_context;

/**
 * @struct s_context_stack_item
 * @brief One nested context and the span it covers.
 *
 * @var s_context_stack_item::end Offset into the owning token value one past
 *                                the last character of the context body.
 * @var s_context_stack_item::start Offset into the owning token value of the
 *                                  first character of the context body.
 * @var s_context_stack_item::context Kind of construct this item records.
 */
typedef struct s_context_stack_item
{
	size_t		end;
	size_t		start;
	t_context	context;
}	t_context_stack_item;

/* ************************************************************************* */
/*                                LIFE_CYCLE                                 */
/* ************************************************************************* */

/**
 * @brief Initializes @p stack as an empty context stack.
 *
 * @param stack Stack initialized by the function (borrowed).
 */
void	context_stack_init(t_context_stack *stack);

/**
 * @brief Frees every item of @p stack, then resets it to a zeroed state.
 *
 * @param stack Already initialized stack (borrowed).
 */
void	context_stack_free(t_context_stack *stack);

/* ************************************************************************* */
/*                             CONTEXT STACK OPS                             */
/* ************************************************************************* */

/**
 * @brief Pops the top (most recently pushed) item of @p stack.
 *
 * @param stack Already initialized stack (borrowed).
 * @param item Set to the popped item; the caller becomes its owner and must
 *             @c free() it (borrowed).
 * @return @c ERR_EMPTY_STACK if @p stack is empty, @c ERR_LIBC if the pop
 *         fails, @c ERR_NO on success.
 */
t_error	context_stack_bpop(t_context_stack *stack, t_context_stack_item **item);

/**
 * @brief Deep-copies every item of @p src into @p dst, preserving order and
 *        the @c start / @c end spans.
 *
 * @param dst Destination stack, already initialized by the caller with
 *            @ref context_stack_init; copied items are appended (borrowed).
 * @param src Source stack (borrowed, read-only).
 * @return @c ERR_INDEX_OUT_OF_BOUND if an item lookup fails, @c ERR_LIBC if
 *         an allocation or push fails, @c ERR_NO on success.
 */
t_error	context_stack_dup(t_context_stack *dst, const t_context_stack *src);

/**
 * @brief Pops the bottom (oldest) item of @p stack.
 *
 * @param stack Already initialized stack (borrowed).
 * @param item Set to the popped item; the caller becomes its owner and must
 *             @c free() it (borrowed).
 * @return @c ERR_EMPTY_STACK if @p stack is empty, @c ERR_LIBC if the
 *         removal fails, @c ERR_NO on success.
 */
t_error	context_stack_fpop(t_context_stack *stack, t_context_stack_item **item);

/**
 * @brief Fetches the item stored at @p index in @p stack without removing it.
 *
 * @param stack Already initialized stack (borrowed, read-only).
 * @param item Set to the item at @p index; @p stack keeps ownership
 *             (borrowed).
 * @param index Position of the item, @c 0 being the bottom of the stack.
 * @return @c ERR_INDEX_OUT_OF_BOUND if @p stack is empty or @p index is past
 *         the last item, @c ERR_NO on success.
 */
t_error	context_stack_get(
			const t_context_stack *stack,
			t_context_stack_item **item,
			size_t index);

/**
 * @brief Allocates a zeroed item recording @p context.
 *
 * @param item Set to the newly allocated item; the caller becomes its owner
 *             until it is pushed with @ref context_stack_push (borrowed).
 * @param context Kind of construct the new item records.
 * @return @c ERR_LIBC if the allocation fails, @c ERR_NO on success.
 */
t_error	context_stack_item_init(t_context_stack_item **item, t_context context);

/**
 * @brief Pushes @p item on top of @p stack.
 *
 * @param stack Already initialized stack (borrowed).
 * @param item Item to push (ownership taken by @p stack).
 * @return @c ERR_LIBC if the push fails, @c ERR_NO on success.
 */
t_error	context_stack_push(t_context_stack *stack, t_context_stack_item *item);

/* ************************************************************************* */
/*                          SUBSTITUTION CONTEXTS                            */
/* ************************************************************************* */

/**
 * @brief Tells whether @p c closes an arithmetic expansion: @c ')' while no
 *        nested parenthesis is open.
 *
 * @note Matches the lexer @c is_end callback signature.
 * @param c Character to test.
 * @param nesting_depth Pointer to the current @c size_t parenthesis nesting
 *                      depth; the function returns @c false if it is @c NULL
 *                      (borrowed, read-only).
 */
bool	is_context_arith_ending(char c, void *nesting_depth);

/**
 * @brief Tells whether @p str starts an arithmetic expansion: @c "$((".
 *
 * @param str NUL-terminated C-string (borrowed, read-only).
 */
bool	is_context_arith_start(char *str);

/**
 * @brief Tells whether @p c closes a backquote command substitution:
 *        @c '`'.
 *
 * @note Matches the lexer @c is_end callback signature.
 * @param c Character to test.
 * @param _ Unused (borrowed, read-only).
 */
bool	is_context_backtick_ending(char c, void *_);

/**
 * @brief Tells whether @p str starts a backquote command substitution:
 *        @c '`'.
 *
 * @param str NUL-terminated C-string (borrowed, read-only).
 */
bool	is_context_backtick_start(char *str);

/**
 * @brief Tells whether @p str starts a command substitution: @c "$(".
 *
 * @note Also matches @c "$((": the caller must test
 *       @ref is_context_arith_start first to disambiguate.
 * @param str NUL-terminated C-string (borrowed, read-only).
 */
bool	is_context_cmd_sub_start(char *str);

/**
 * @brief Tells whether @p c closes a parameter expansion: @c '}'.
 *
 * @note Matches the lexer @c is_end callback signature.
 * @param c Character to test.
 * @param _ Unused (borrowed, read-only).
 */
bool	is_context_param_ending(char c, void *_);

/**
 * @brief Tells whether @p str starts a parameter expansion: @c "${".
 *
 * @param str NUL-terminated C-string (borrowed, read-only).
 */
bool	is_context_param_start(char *str);

/**
 * @brief Tells whether a backslash escapes @p c inside backquotes nested in
 *        double quotes or arithmetic expansion: @c '$', @c '`', @c '"' or
 *        @c '\\'.
 *
 * @param c Character to test.
 */
bool	is_in_context_backtick_special_whitelist(char c);

/**
 * @brief Tells whether a backslash escapes @p c inside backquotes: @c '$',
 *        @c '`' or @c '\\'.
 *
 * @param c Character to test.
 */
bool	is_in_context_backtick_whitelist(char c);

/**
 * @brief Tells whether a backslash escapes @p c inside a parameter
 *        expansion: always @c true.
 *
 * @param c Character to test.
 */
bool	is_in_context_param_whitelist(char c);

/**
 * @brief Dispatches to the escape whitelist of @p context, for the
 *        substitution contexts @c CONTEXT_NONE, @c CONTEXT_PARAM and
 *        @c CONTEXT_BACKTICK.
 *
 * @param c Character to test.
 * @param context Context to test @p c against; any other context yields
 *                @c false.
 */
bool	is_in_substitution_whitelist(char c, t_context context);

/**
 * @brief Tells whether @p str starts a substitution construct and, if so,
 *        which one.
 *
 * @param str NUL-terminated C-string (borrowed, read-only).
 * @param context Set to the detected context (@c CONTEXT_PARAM,
 *                @c CONTEXT_ARITH, @c CONTEXT_CMD_SUB or
 *                @c CONTEXT_BACKTICK); untouched when the function returns
 *                @c false (borrowed).
 */
bool	is_substitution_context(char *str, t_context *context);

/* ************************************************************************* */
/*                               NONE CONTEXT                                */
/* ************************************************************************* */

/**
 * @brief Tells whether @p c is a blank: space or tab.
 *
 * @param c Character to test.
 */
bool	is_blank(char c);

/**
 * @brief Tells whether @p c ends the top-level context: @c '\0'.
 *
 * @note Matches the lexer @c is_end callback signature.
 * @param c Character to test.
 * @param _ Unused (borrowed, read-only).
 */
bool	is_context_none_ending(char c, void *_);

/**
 * @brief Tells whether a backslash escapes @p c at top level: always
 *        @c true.
 *
 * @param c Character to test.
 */
bool	is_in_context_none_whitelist(char c);

/* ************************************************************************* */
/*                             QUOTING CONTEXTS                              */
/* ************************************************************************* */

/**
 * @brief Tells whether @p c closes an ANSI-C quoted string: @c '\''.
 *
 * @note Matches the lexer @c is_end callback signature.
 * @param c Character to test.
 * @param _ Unused (borrowed, read-only).
 */
bool	is_context_dollar_squote_ending(char c, void *_);

/**
 * @brief Tells whether @p str starts an ANSI-C quoted string: @c "$'".
 *
 * @param str NUL-terminated C-string (borrowed, read-only).
 */
bool	is_context_dollar_squote_start(char *str);

/**
 * @brief Tells whether @p c closes a double-quoted string: @c '"'.
 *
 * @note Matches the lexer @c is_end callback signature.
 * @param c Character to test.
 * @param _ Unused (borrowed, read-only).
 */
bool	is_context_dquote_ending(char c, void *_);

/**
 * @brief Tells whether @p str starts a double-quoted string: @c '"'.
 *
 * @param str NUL-terminated C-string (borrowed, read-only).
 */
bool	is_context_dquote_start(char *str);

/**
 * @brief Tells whether @p c ends a here-document body: @c '\0'.
 *
 * @note Matches the lexer @c is_end callback signature. There is no
 *       here-document start detector: the lexer enters @c CONTEXT_HEREDOC
 *       itself when reading a here-document body.
 * @param c Character to test.
 * @param _ Unused (borrowed, read-only).
 */
bool	is_context_heredoc_ending(char c, void *_);

/**
 * @brief Tells whether @p context is one of the quoting contexts:
 *        @c CONTEXT_SQUOTE, @c CONTEXT_DQUOTE or @c CONTEXT_DOLLAR_SQUOTE.
 *
 * @note @c CONTEXT_HEREDOC is not a quoting context.
 * @param context Context to classify.
 */
bool	is_context_quoting(t_context context);

/**
 * @brief Tells whether @p c closes a single-quoted string: @c '\''.
 *
 * @note Matches the lexer @c is_end callback signature.
 * @param c Character to test.
 * @param _ Unused (borrowed, read-only).
 */
bool	is_context_squote_ending(char c, void *_);

/**
 * @brief Tells whether @p str starts a single-quoted string: @c '\''.
 *
 * @param str NUL-terminated C-string (borrowed, read-only).
 */
bool	is_context_squote_start(char *str);

/**
 * @brief Tells whether a backslash escapes @p c inside an ANSI-C quoted
 *        string: always @c true.
 *
 * @param c Character to test.
 */
bool	is_in_context_dollar_squote_whitelist(char c);

/**
 * @brief Tells whether a backslash escapes @p c inside double quotes:
 *        @c '$', @c '`', @c '\\' or @c '"'.
 *
 * @param c Character to test.
 */
bool	is_in_context_dquote_whitelist(char c);

/**
 * @brief Tells whether @p c keeps its special meaning inside a here-document
 *        body: @c '$', @c '`' or @c '\\'.
 *
 * @param c Character to test.
 */
bool	is_in_context_heredoc_whitelist(char c);

/**
 * @brief Tells whether a backslash escapes @p c inside single quotes:
 *        always @c false, everything is literal.
 *
 * @param c Character to test.
 */
bool	is_in_context_squote_whitelist(char c);

/**
 * @brief Dispatches to the escape whitelist of @p context, for
 *        @c CONTEXT_NONE, the quoting contexts and @c CONTEXT_HEREDOC.
 *
 * @param c Character to test.
 * @param context Context to test @p c against; any other context yields
 *                @c false.
 */
bool	is_in_quoting_whitelist(char c, t_context context);

/**
 * @brief Tells whether @p str starts a quoting construct and, if so, which
 *        one.
 *
 * @param str NUL-terminated C-string (borrowed, read-only).
 * @param context Set to the detected context (@c CONTEXT_SQUOTE,
 *                @c CONTEXT_DOLLAR_SQUOTE or @c CONTEXT_DQUOTE); untouched
 *                when the function returns @c false (borrowed).
 */
bool	is_quoting_context(char *str, t_context *context);

/**
 * @brief Dispatches to the ending detector of @p context, for the quoting
 *        contexts only.
 *
 * @param c Character to test.
 * @param context Context to test @p c against; any non-quoting context
 *                (including @c CONTEXT_HEREDOC) yields @c false.
 */
bool	is_quoting_ending(char c, t_context context);

#endif
