#ifndef ALIAS_STACK__H
# define ALIAS_STACK__H

# include "error.h"
# include "alias.h"

/*
 * The t_alias_stack type (a vector of owned alias-name strings) is declared
 * in alias.h; this header documents the operations on it. The stack records
 * the aliases currently being expanded to break expansion recursion.
 */

/**
 * @ingroup alias
 * @brief Initialises an empty expansion stack.
 *
 * @param stack Pointer to the stack to initialise (borrowed).
 */
void	alias_stack_init(t_alias_stack *stack);

/**
 * @ingroup alias
 * @brief Frees the stack and every name it owns.
 *
 * @param stack Pointer to the stack to free (borrowed).
 */
void	alias_stack_free(t_alias_stack *stack);

/**
 * @ingroup alias
 * @brief Pops and frees the top alias name.
 *
 * Does nothing when the stack is empty.
 *
 * @param stack Pointer to the stack (borrowed).
 */
void	alias_stack_pop(t_alias_stack *stack);

/**
 * @ingroup alias
 * @brief Pushes an alias name, taking ownership of @p item.
 *
 * @param stack Pointer to the stack (borrowed).
 * @param item Alias name whose ownership is transferred to the stack.
 * @return ERR_NO on success, ERR_LIBC on allocation failure.
 */
t_error	alias_stack_push(t_alias_stack *stack, char *item);

/**
 * @ingroup alias
 * @brief Tests whether an alias name is currently being expanded.
 *
 * @param stack Pointer to the stack (borrowed).
 * @param word Alias name to look for (borrowed).
 * @return true if @p word is on the stack, false otherwise.
 */
bool	alias_stack_contains(t_alias_stack *stack, char *word);

#endif
