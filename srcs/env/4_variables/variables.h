#ifndef VARIABLES_H
# define VARIABLES_H

# include "libft.h"
# include "error.h"
# include <stdbool.h>

/* ************************************************************************* */
/*                                   TYPES                                   */
/* ************************************************************************* */

typedef t_hashmap	t_var_list;

/**
 * @enum e_var_print_mode
 * @brief Output mode used by @ref var_print().
 */
typedef enum e_var_print_mode
{
	VAR_PRINT_EXPORT,
	VAR_PRINT_READONLY,
	VAR_PRINT_SET
}	t_var_print_mode;

/* ************************************************************************* */
/*                                 LIFE CYCLE                                */
/* ************************************************************************* */

void	var_init(t_var_list *variables);

t_error	var_load(t_var_list *variables, char **envp);

void	var_clear(t_var_list *variables);

void	var_free(t_var_list *variables);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

t_error	var_build_envp(const t_var_list *variables, t_vector *dst_envp);

t_error	var_get(const t_string *name, t_string *dst_val);

t_error	var_get_from_const(const char *name, t_string *dst_val);

bool	var_is_readonly(const t_var_list *variables, const char *name);

t_error	var_print(t_var_print_mode mode);

t_error	var_set(
			const t_string *name,
			const t_string *value,
			bool export,
			bool rdonly);

t_error	var_unset(const t_string *name);

#endif
