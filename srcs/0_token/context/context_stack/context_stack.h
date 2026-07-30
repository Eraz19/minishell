#ifndef CONTEXT_STACK_H
# define CONTEXT_STACK_H

# include "libft.h"
# include "error.h"

/* ************************************************************************* */
/*                             TYPE FORWARDING                               */
/* ************************************************************************* */

typedef struct s_context_stack_item	t_context_stack_item;

/* ************************************************************************* */
/*                                  TYPES                                    */
/* ************************************************************************* */

typedef t_vector					t_context_stack;

/* ************************************************************************* */
/*                                LIFE CYCLE                                 */
/* ************************************************************************* */

void	context_stack_init(t_context_stack *stack);

void	context_stack_free(t_context_stack *stack);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

t_error	context_stack_dup(t_context_stack *dst, const t_context_stack *src);

t_error	context_stack_push(t_context_stack *stack, t_context_stack_item *item);

void	context_stack_bpop(t_context_stack *stack, t_context_stack_item **item);

void	context_stack_fpop(t_context_stack *stack, t_context_stack_item **item);

void	context_stack_get(const t_context_stack *stack, t_context_stack_item **item, size_t index);

#endif
