#ifndef VARIABLES_H
# define VARIABLES_H

# include "libft.h"
# include "error.h"

/* ************************************************************************* */
/*                                   TYPES                                   */
/* ************************************************************************* */

typedef struct s_var
{
	char	*name;
	char	*value;
	bool	export;
	bool	readonly;
}	t_var;

typedef t_vector	t_var_list;

/* ************************************************************************* */
/*                         LIFE CYCLE (one variable)                         */
/* ************************************************************************* */

// @warning: can fail (ERR_LIBC), caller must check name is not NULL
t_var	var_new(const char *name, const char *value, bool export, bool ronly);

void	var_free(void *var);

/* ************************************************************************* */
/*                         LIFE CYCLE (variable list)                        */
/* ************************************************************************* */

void	var_init_all(t_var_list *variables);

// parent_shell_ppid can be NULL (if it is not a subshell).
// ERR_VAR_INVALID_NAME / ERR_VAR_NOT_FOUND / ERR_VAR_READ_ONLY / ERR_LIBC.
t_error	var_load_all(
	t_var_list *variables,
	char **envp,
	const char *parent_shell_ppid);

void	var_free_all(t_var_list *variables);

/* ************************************************************************* */
/*                                   CORE                                    */
/* ************************************************************************* */

bool	var_find(const t_var_list *variables, const char *name, size_t *res);

// @warning: *dst_val can be NULL if var->value == NULL (error will be ERR_NO).
// @ret ERR_VAR_NOT_FOUND / ERR_LIBC.
t_error	var_get(const t_var_list *variables, const char *name, char **dst_val);

bool	var_name_is_valid(const char *name);

// @ret ERR_LIBC
t_error	var_print(const char *prefix, const t_var *var);

// value can be NULL.
// @ret ERR_VAR_INVALID_NAME / ERR_VAR_READ_ONLY / ERR_LIBC.
t_error	var_set(t_var_list *variables, const char *name, const char *value);

// @ret ERR_VAR_MISSING_EQUAL / ERR_LIBC
t_error	var_split(const char *src, char **dst_name, char **dst_value);

#endif
