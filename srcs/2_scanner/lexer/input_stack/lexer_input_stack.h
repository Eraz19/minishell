#ifndef INPUT_STACK_H
# define INPUT_STACK_H

# include "libft.h"
# include "error.h"
# include "lexer_input_stack_item.h"

/* ************************************************************************* */
/*                                  TYPES                                    */
/* ************************************************************************* */

/**
 * @ingroup lexer
 * @typedef t_lexer_input_stack
 * @brief Stack of lexer inputs (root input plus alias expansions), backed
 *        by a @ref t_vector of @ref t_lexer_input_stack_item values (owned
 *        by the stack).
 */
typedef t_vector	t_lexer_input_stack;

/* ************************************************************************* */
/*                                LIFE_CYCLE                                 */
/* ************************************************************************* */

/**
 * @ingroup lexer
 * @brief Initializes @p stack as an empty input stack.
 *
 * @param stack Stack to initialize; initialized by the function (borrowed).
 */
void	lexer_input_stack_init(t_lexer_input_stack *stack);

/**
 * @ingroup lexer
 * @brief Frees every stacked item and the stack storage.
 *
 * @param stack Already initialized stack (borrowed).
 */
void	lexer_input_stack_free(t_lexer_input_stack *stack);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup lexer
 * @brief Deep-copies @p in into @p out, duplicating each item text, read
 *        cursor and @c alias_position_exempt flag.
 *
 * @param out Destination stack; initialized by the function, and freed by
 *            the function on failure (borrowed).
 * @param in Already initialized source stack (borrowed, read-only).
 * @return @c ERR_NO on success, @c ERR_LIBC on allocation failure.
 */
t_error	lexer_input_stack_dup(t_lexer_input_stack *out,
			const t_lexer_input_stack *in);

/**
 * @ingroup lexer
 * @brief Points @p item at the top item of @p stack.
 *
 * @warning @p stack must not be empty (asserted).
 * @warning The returned pointer aims into the stack storage: any push or
 *          pop may move or free it, so it must be re-fetched after every
 *          stack mutation and never freed through @p item.
 *
 * @param stack Already initialized, non-empty stack (borrowed).
 * @param item Receives the address of the top item (borrowed).
 */
void	lexer_input_stack_get_last(
			t_lexer_input_stack *stack,
			t_lexer_input_stack_item **item);

/**
 * @ingroup lexer
 * @brief Pops the top item of @p stack and frees it.
 *
 * @warning @p stack must not be empty (asserted).
 *
 * @param stack Already initialized, non-empty stack (borrowed).
 */
void	lexer_input_stack_pop(t_lexer_input_stack *stack);

/**
 * @ingroup lexer
 * @brief Appends @p item on top of @p stack.
 *
 * @warning On failure the item is not stacked and the caller keeps
 *          ownership of its resources.
 *
 * @param stack Already initialized stack (borrowed).
 * @param item Item to push (ownership taken by the stack).
 * @return @c ERR_NO on success, @c ERR_LIBC on allocation failure.
 */
t_error	lexer_input_stack_push(t_lexer_input_stack *stack,
			t_lexer_input_stack_item *item);

#endif
