#ifndef VARIABLES_H
# define VARIABLES_H

# include "libft.h"
# include "error.h"
# include <stdbool.h>

/* ************************************************************************* */
/*                                   TYPES                                   */
/* ************************************************************************* */

typedef t_vector	t_var_list;

typedef enum e_var_print_mode
{
	VAR_PRINT_EXPORT,
	VAR_PRINT_READONLY
}	t_var_print_mode;

/* ************************************************************************* */
/*                                 LIFE CYCLE                                */
/* ************************************************************************* */

void	var_init(t_var_list *variables);

// ERR_VAR_INVALID_NAME / ERR_VAR_NOT_FOUND / ERR_VAR_READ_ONLY / ERR_LIBC.
t_error	var_load(t_var_list *variables, char **envp);

void	var_free(t_var_list *variables);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

// @warning: *dst_val can be NULL if var->value == NULL (error will be ERR_NO).
// @ret ERR_SHELL_NOT_FOUND / ERR_VAR_INVALID_NAME / ERR_VAR_NOT_FOUND
// 		/ ERR_LIBC.
t_error	var_get(const char *name, char **dst_val);

// @ret ERR_SHELL_NOT_FOUND / ERR_LIBC
t_error	var_print(t_var_print_mode mode);

// value can be NULL.
// export == false and rdonly == false are ignored if variable already exists
// if variable doesn't exist yet and option_is_active(OPT_EXPORT_ALL)
// 		=> export will be set to true even if export == false
// @ret ERR_SHELL_NOT_FOUND / ERR_VAR_INVALID_NAME / ERR_VAR_READ_ONLY
// 		/ ERR_LIBC.
t_error	var_set(const char *name, const char *value, bool export, bool rdonly);

/* ************************************************************************* */
/*                                   DEBUG                                   */
/* ************************************************************************* */

void	var_dump(void);

#endif
