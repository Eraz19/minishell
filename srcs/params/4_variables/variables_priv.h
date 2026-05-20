#ifndef VARIABLES_PRIV_H
# define VARIABLES_PRIV_H

# include "variables.h"
# include "error.h"
# include <stddef.h>

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

/* ************************************************************************* */
/*                                LIFE CYCLE                                 */
/* ************************************************************************* */

// @warning: if name var.name == NULL => ERR_LIBC
t_var	var_new(const char *name, const char *value, bool export, bool ronly);
void	var_free_one(void *var);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

// @ret ERR_VAR_MISSING_EQUAL / ERR_LIBC
t_error	var_split(const char *src, char **dst_name, char **dst_value);
bool	var_name_is_valid(const char *name);
bool	var_find(const t_var_list *variables, const char *name, size_t *res);

/* ************************************************************************* */
/*                                   DEBUG                                   */
/* ************************************************************************* */

void	var_dump_one(t_var *var);

#endif
