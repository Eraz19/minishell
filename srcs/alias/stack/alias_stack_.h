#ifndef ALIAS_STACK__H
# define ALIAS_STACK__H

# include "error.h"
# include "_OLD_alias.h"

/** @defgroup alias_stack Alias recursion-guard stack
 *  @brief Records the aliases currently being expanded to break expansion
 *         recursion (POSIX 2.3.1).
 *
 *  The @ref t_alias_stack type (a @ref t_vector of owned alias-name
 *  C-strings) is declared in alias.h; this header documents the
 *  operations on it.
 */

/* ************************************************************************* */
/*                                LIFE_CYCLE                                 */
/* ************************************************************************* */

/**
 * @ingroup alias_stack
 * @brief Initializes @p stack as an empty expansion stack.
 *
 * @param stack Stack initialized by the function (borrowed).
 */
void	alias_stack_init(t_alias_stack *stack);

// TODO: doc
void	alias_stack_clear(t_alias_stack *stack);

/**
 * @ingroup alias_stack
 * @brief Frees @p stack and every name it owns.
 *
 * @param stack Already initialized stack (borrowed).
 */
void	alias_stack_free(t_alias_stack *stack);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup alias_stack
 * @brief Tests whether an alias name is currently being expanded.
 *
 * @param stack Already initialized stack (borrowed, read-only).
 * @param word Alias name to look for, NUL-terminated C-string
 *             (borrowed, read-only).
 * @return True if @p word is on the stack, false otherwise.
 */
bool	alias_stack_contains(t_alias_stack *stack, char *word);

/**
 * @ingroup alias_stack
 * @brief Pops and frees the top alias name.
 *
 * Does nothing when the stack is empty.
 *
 * @param stack Already initialized stack (borrowed).
 */
void	alias_stack_pop(t_alias_stack *stack);

/**
 * @ingroup alias_stack
 * @brief Pushes an alias name on the stack.
 *
 * @warning Ownership is conditional: @p item is owned by the stack on
 *          success, but stays owned by the caller on failure (the caller
 *          must free it, as @c alias_expand_token does).
 * @param stack Already initialized stack (borrowed).
 * @param item Heap-allocated alias name (ownership taken by @p stack on
 *             success only).
 * @return @c ERR_LIBC if the push fails, @c ERR_NO on success.
 */
// TODO: fix ownership
t_error	alias_stack_push(t_alias_stack *stack, char *item);

#endif
