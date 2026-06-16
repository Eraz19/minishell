/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_stack_.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 17:03:49 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/10 19:01:10 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_STACK__H
# define INPUT_STACK__H

# include "context.h"

/**
 * @ingroup scanner
 * @brief Stack of input sources, innermost on top (a vector of item pointers).
 *
 * The base input sits at the bottom; alias expansions and line continuations
 * are pushed on top and popped when exhausted, so the lexer always reads from
 * the topmost item.
 */
typedef t_vector	t_input_stack;

/**
 * @ingroup scanner
 * @struct s_input_stack_item
 * @brief One input source: its text, a read cursor and its own context stack.
 *
 * Items are heap-allocated; the stack stores pointers to them so growth never
 * moves a live item out from under the lexer's borrowed pointer.
 *
 * @var s_input_stack_item::i Read cursor (index into str).
 * @var s_input_stack_item::str Owned input text (NUL-terminated).
 * @var s_input_stack_item::context Per-input stack of open quoting/expansion
 *                                  contexts.
 */
typedef struct s_input_stack_item
{
	size_t			i;
	char			*str;
	t_context_stack	context;
}	t_input_stack_item;

/**
 * @ingroup scanner
 * @brief Initialises an empty input stack (a vector of item pointers).
 * @param stack Pointer to the stack to initialise (borrowed).
 */
void	input_stack_init(t_input_stack *stack);

/**
 * @ingroup scanner
 * @brief Frees the stack and every item it still holds.
 * @param stack Pointer to the stack to free (borrowed).
 */
void	input_stack_free(t_input_stack *stack);

/**
 * @ingroup scanner
 * @brief Frees one input item: its text, its context stack and the item.
 *
 * Takes the address of the stored pointer (matching the vector destructor
 * signature) and releases both the item's contents and the allocation itself.
 *
 * @param item Address of the stored item pointer (t_input_stack_item **).
 */
void	input_stack_item_free(void *item);

/**
 * @ingroup scanner
 * @brief Allocates and zero-initialises a new input item.
 *
 * @param item Out-parameter receiving the freshly allocated item.
 * @return ERR_NO on success, ERR_LIBC on allocation failure.
 */
t_error	input_stack_item_init(t_input_stack_item **item);

/**
 * @ingroup scanner
 * @brief Removes the top input item and frees it.
 * @param stack Pointer to the stack (borrowed).
 * @return ERR_NO on success, ERR_LIBC on internal failure.
 */
t_error	input_stack_pop(t_input_stack *stack);

/**
 * @ingroup scanner
 * @brief Pushes an item pointer as the new top of the stack.
 *
 * Ownership of @p item transfers to the stack.
 *
 * @param stack Pointer to the stack (borrowed).
 * @param item Item to push (ownership transferred).
 * @return ERR_NO on success, ERR_LIBC on allocation failure.
 */
t_error	input_stack_push(t_input_stack *stack, t_input_stack_item *item);

/**
 * @ingroup scanner
 * @brief Reads the top input item without removing it.
 * @param stack Pointer to the stack (borrowed).
 * @param item Out-parameter receiving the borrowed top item pointer.
 * @return ERR_NO on success, ERR_EMPTY_STACK if the stack is empty.
 */
t_error	input_stack_get_last(t_input_stack *stack, t_input_stack_item **item);

#endif
