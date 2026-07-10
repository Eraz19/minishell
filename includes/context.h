#ifndef CONTEXT_H
# define CONTEXT_H

# include "error.h"
# include "libft.h"

/* ************************************************************************* */
/*                                   TYPES                                   */
/* ************************************************************************* */

/**
 * @brief Stack of @ref t_context_stack_item pointers backed by a @ref t_vector.
 */
typedef t_vector	t_context_stack;

/**
 * @enum e_context
 * @brief Lexing and expansion contexts recognized by the shell.
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
 * @brief One context span stored inside a @ref t_context_stack.
 *
 * @var s_context_stack_item::end End offset associated with the context span.
 * @var s_context_stack_item::start Start offset associated with the context span.
 * @var s_context_stack_item::context Context kind tracked by this item.
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
 * @brief Release every item stored in @p stack and reset the stack.
 *
 * @param stack Context stack to free (borrowed).
 */
void	context_stack_free(t_context_stack *stack);

/**
 * @brief Initialize an empty @ref t_context_stack.
 *
 * @param stack Destination stack initialized by the function (borrowed).
 */
void	context_stack_init(t_context_stack *stack);

/**
 * @brief Allocate and initialize one context stack item.
 *
 * The resulting item starts with zeroed offsets and with @p context as its
 * context kind.
 *
 * @param item Destination receiving the allocated item pointer, initialized by
 *             the function (borrowed).
 * @param context Context kind stored in the new item.
 * @return @c ERR_NO or @c ERR_LIBC.
 */
t_error	context_stack_item_init(t_context_stack_item **item, t_context context);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @brief Remove and return the last item stored in @p stack.
 *
 * @param stack Context stack to update in place (borrowed).
 * @param item Destination receiving the removed item when non-NULL
 *             (ownership taken by caller).
 * @return @c ERR_NO, @c ERR_EMPTY_STACK or @c ERR_LIBC.
 */
t_error	context_stack_bpop(t_context_stack *stack, t_context_stack_item **item);

/**
 * @brief Duplicate every item from @p src into @p dst.
 *
 * @warning @p dst must already be initialized by the caller.
 *
 * @param dst Destination stack receiving deep-copied items (borrowed).
 * @param src Source stack to duplicate (borrowed, read-only).
 * @return @c ERR_NO or @c ERR_LIBC.
 */
t_error	context_stack_dup(t_context_stack *dst, const t_context_stack *src);

/**
 * @brief Remove and return the first item stored in @p stack.
 *
 * @param stack Context stack to update in place (borrowed).
 * @param item Destination receiving the removed item when non-NULL
 *             (ownership taken by caller).
 * @return @c ERR_NO, @c ERR_EMPTY_STACK or @c ERR_LIBC.
 */
t_error	context_stack_fpop(t_context_stack *stack, t_context_stack_item **item);

/**
 * @brief Read the item stored at @p index without removing it.
 *
 * @param stack Context stack to inspect (borrowed, read-only).
 * @param item Destination receiving the borrowed item pointer (borrowed).
 * @param index Zero-based item index to read.
 * @return @c ERR_NO, @c ERR_EMPTY_STACK or @c ERR_INDEX_OUT_OF_BOUND.
 */
t_error	context_stack_get(
			const t_context_stack *stack,
			t_context_stack_item **item,
			size_t index);

/**
 * @brief Push @p item at the end of @p stack.
 *
 * @param stack Context stack to update in place (borrowed).
 * @param item Item to append (ownership taken by t_context_stack).
 * @return @c ERR_NO or @c ERR_LIBC.
 */
t_error	context_stack_push(t_context_stack *stack, t_context_stack_item *item);

/**
 * @brief Report whether @p c is treated as blank in shell lexical contexts.
 *
 * @param c Character to classify.
 * @return True for space and horizontal tab, false otherwise.
 */
bool	is_blank(char c);

/**
 * @brief Report whether @p context is one of the quoting contexts.
 *
 * @param context Context kind to classify.
 * @return True for @c CONTEXT_SQUOTE, @c CONTEXT_DQUOTE and
 *         @c CONTEXT_DOLLAR_SQUOTE, false otherwise.
 */
bool	is_context_quoting(t_context context);

/**
 * @brief Report whether @p str starts an arithmetic expansion.
 *
 * @param str Candidate input slice to inspect (borrowed, read-only).
 * @return True when @p str starts with @c "$((", false otherwise.
 */
bool	is_context_arith_start(char *str);

/**
 * @brief Report whether @p c ends an arithmetic expansion at the current depth.
 *
 * @param c Character to classify.
 * @param nesting_depth Pointer to the current arithmetic nesting depth or
 *                      @c NULL (borrowed).
 * @return True when @p c is @c ')' and @p nesting_depth points to zero, false
 *         otherwise.
 */
bool	is_context_arith_ending(char c, void *nesting_depth);

/**
 * @brief Report whether @p str starts a backtick command substitution.
 *
 * @param str Candidate input slice to inspect (borrowed, read-only).
 * @return True when the first character is @c '`', false otherwise.
 */
bool	is_context_backtick_start(char *str);

/**
 * @brief Report whether @p c ends a backtick command substitution.
 *
 * @param c Character to classify.
 * @param _ Unused callback state.
 * @return True when @p c is @c '`', false otherwise.
 */
bool	is_context_backtick_ending(char c, void *_);

/**
 * @brief Report whether @p str starts a command substitution.
 *
 * @param str Candidate input slice to inspect (borrowed, read-only).
 * @return True when @p str starts with @c "$(", false otherwise.
 */
bool	is_context_cmd_sub_start(char *str);

/**
 * @brief Report whether @p str starts ANSI-C quoting.
 *
 * @param str Candidate input slice to inspect (borrowed, read-only).
 * @return True when @p str starts with @c "$'", false otherwise.
 */
bool	is_context_dollar_squote_start(char *str);

/**
 * @brief Report whether @p c ends ANSI-C quoting.
 *
 * @param c Character to classify.
 * @param _ Unused callback state.
 * @return True when @p c is @c '\'', false otherwise.
 */
bool	is_context_dollar_squote_ending(char c, void *_);

/**
 * @brief Report whether @p str starts double quoting.
 *
 * @param str Candidate input slice to inspect (borrowed, read-only).
 * @return True when the first character is @c '"', false otherwise.
 */
bool	is_context_dquote_start(char *str);

/**
 * @brief Report whether @p c ends double quoting.
 *
 * @param c Character to classify.
 * @param _ Unused callback state.
 * @return True when @p c is @c '"', false otherwise.
 */
bool	is_context_dquote_ending(char c, void *_);

/**
 * @brief Report whether @p c ends the here-document body context.
 *
 * @param c Character to classify.
 * @param _ Unused callback state.
 * @return True when @p c is @c '\0', false otherwise.
 */
bool	is_context_heredoc_ending(char c, void *_);

/**
 * @brief Report whether @p c ends the top-level context.
 *
 * @param c Character to classify.
 * @param _ Unused callback state.
 * @return True when @p c is @c '\0', false otherwise.
 */
bool	is_context_none_ending(char c, void *_);

/**
 * @brief Report whether @p str starts a parameter expansion.
 *
 * @param str Candidate input slice to inspect (borrowed, read-only).
 * @return True when @p str starts with @c "${", false otherwise.
 */
bool	is_context_param_start(char *str);

/**
 * @brief Report whether @p c ends a parameter expansion.
 *
 * @param c Character to classify.
 * @param _ Unused callback state.
 * @return True when @p c is @c '}', false otherwise.
 */
bool	is_context_param_ending(char c, void *_);

/**
 * @brief Report whether @p str starts single quoting.
 *
 * @param str Candidate input slice to inspect (borrowed, read-only).
 * @return True when the first character is @c '\'', false otherwise.
 */
bool	is_context_squote_start(char *str);

/**
 * @brief Report whether @p c ends single quoting.
 *
 * @param c Character to classify.
 * @param _ Unused callback state.
 * @return True when @p c is @c '\'', false otherwise.
 */
bool	is_context_squote_ending(char c, void *_);

/**
 * @brief Report whether @p c is allowed to trigger special handling inside a
 *        backtick context.
 *
 * @param c Character to classify.
 * @return True for @c '$', @c '`', @c '"' and @c '\\', false otherwise.
 */
bool	is_in_context_backtick_special_whitelist(char c);

/**
 * @brief Report whether @p c is recognized specially inside a backtick context.
 *
 * @param c Character to classify.
 * @return True for @c '\\', @c '$' and @c '`', false otherwise.
 */
bool	is_in_context_backtick_whitelist(char c);

/**
 * @brief Report whether every character stays literal inside ANSI-C quoting.
 *
 * @param c Character to classify.
 * @return Always true.
 */
bool	is_in_context_dollar_squote_whitelist(char c);

/**
 * @brief Report whether @p c is recognized specially inside double quotes.
 *
 * @param c Character to classify.
 * @return True for @c '$', @c '`', @c '\\' and @c '"', false otherwise.
 */
bool	is_in_context_dquote_whitelist(char c);

/**
 * @brief Report whether @p c is recognized specially inside a here-document
 *        body.
 *
 * @param c Character to classify.
 * @return True for @c '$', @c '`' and @c '\\', false otherwise.
 */
bool	is_in_context_heredoc_whitelist(char c);

/**
 * @brief Report whether every character is accepted in the top-level context.
 *
 * @param c Character to classify.
 * @return Always true.
 */
bool	is_in_context_none_whitelist(char c);

/**
 * @brief Report whether every character is accepted inside a parameter
 *        expansion.
 *
 * @param c Character to classify.
 * @return Always true.
 */
bool	is_in_context_param_whitelist(char c);

/**
 * @brief Report whether every character stays literal inside single quotes.
 *
 * @param c Character to classify.
 * @return Always false.
 */
bool	is_in_context_squote_whitelist(char c);

/**
 * @brief Dispatch the whitelist predicate associated with one quoting context.
 *
 * @param c Character to classify.
 * @param context Quoting context to inspect.
 * @return The result of the matching quoting whitelist predicate, or false for
 *         unsupported contexts.
 */
bool	is_in_quoting_whitelist(char c, t_context context);

/**
 * @brief Dispatch the whitelist predicate associated with one substitution
 *        context.
 *
 * @param c Character to classify.
 * @param context Substitution context to inspect.
 * @return The result of the matching substitution whitelist predicate, or
 *         false for unsupported contexts.
 */
bool	is_in_substitution_whitelist(char c, t_context context);

/**
 * @brief Detect the quoting context started at @p str.
 *
 * @param str Candidate input slice to inspect (borrowed, read-only).
 * @param context Destination receiving the detected quoting context on success
 *                (borrowed).
 * @return True when @p str starts a quoting context, false otherwise.
 */
bool	is_quoting_context(char *str, t_context *context);

/**
 * @brief Dispatch the ending predicate associated with one quoting context.
 *
 * @param c Character to classify.
 * @param context Quoting context to inspect.
 * @return The result of the matching quoting ending predicate, or false for
 *         unsupported contexts.
 */
bool	is_quoting_ending(char c, t_context context);

/**
 * @brief Detect the substitution context started at @p str.
 *
 * @param str Candidate input slice to inspect (borrowed, read-only).
 * @param context Destination receiving the detected substitution context on
 *                success (borrowed).
 * @return True when @p str starts a substitution context, false otherwise.
 */
bool	is_substitution_context(char *str, t_context *context);

#endif
