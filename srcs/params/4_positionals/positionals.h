#ifndef POSITIONALS_H
# define POSITIONALS_H

# include "libft.h"
# include "error.h"

typedef struct s_positionals
{
	char	**params;	// $@ / $* / $n
	size_t	count;		// $#
}	t_positionals;

typedef t_vector	t_positionals_stack;

/* ************************************************************************* */
/*                                LIFE CYCLE                                 */
/* ************************************************************************* */

void	positionals_init(t_positionals_stack *stack);

// @ret ERR_NO / ERR_LIBC
t_error	positionals_load(
	t_positionals_stack *stack,
	int argc,
	char **argv,
	size_t start_index);

void	positionals_free(t_positionals_stack *stack);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

// @ret ERR_NO / ERR_LIBC
t_error	positionals_push(
	t_positionals_stack *stack,
	t_positionals *positionals);

// @ret ERR_NO / ERR_LIBC
t_error	positionals_pop(t_positionals_stack *stack);

// @ret ERR_NO / ERR_LIBC
t_error	positionals_replace(
	t_positionals_stack *stack,
	t_positionals *positionals);

// @ret ERR_NO / ERR_VAR_NOT_FOUND
t_error	positionals_get(const t_positionals_stack *stack, t_positionals *dst);

// @ret ERR_NO / ERR_VAR_NOT_FOUND / ERR_LIBC
t_error	positionals_get_one(
	const t_positionals_stack *stack,
	const char *name,
	char **dst);

#endif
