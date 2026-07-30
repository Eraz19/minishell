#ifndef ALIAS_STACK_H
# define ALIAS_STACK_H

# include "libft.h"
# include "error.h"

/** @defgroup alias_stack Alias recursion-guard stack
 *  @brief Records the aliases currently being expanded to break expansion
 *         recursion (POSIX 2.3.1).
 *
 *  The @ref t_alias_stack type (a @ref t_vector of owned alias-name
 *  C-strings) is declared in alias.h; this header documents the
 *  operations on it.
 */

/**
 * @ingroup alias
 * @typedef t_alias_stack
 * @brief Recursion-guard stack: the names currently being expanded,
 *        backed by a @ref t_vector of owned C-strings.
 */
typedef t_vector	t_alias_stack;

/* ************************************************************************* */
/*                                LIFE_CYCLE                                 */
/* ************************************************************************* */

void	alias_stack_init(t_alias_stack *stack);

void	alias_stack_free(t_alias_stack *stack);

void	alias_stack_clear(t_alias_stack *stack);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

void	alias_stack_pop(t_alias_stack *stack);

t_error	alias_stack_push(t_alias_stack *stack, char *item);

bool	alias_stack_contains(t_alias_stack *stack, char *word);

#endif
