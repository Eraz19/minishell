#ifndef VARIABLE_H
# define VARIABLE_H

# include "libft.h"
# include "error.h"

typedef struct s_var
{
	char	*name;
	char	*value;
	bool	export;
	bool	readonly;
}	t_var;

typedef t_vector	t_var_list;

/* ************************************************************************* */
/*                                LIFE CYCLE                                 */
/* ************************************************************************* */

void	var_free(t_var *var);

/* ************************************************************************* */
/*                                  HELPERS                                  */
/* ************************************************************************* */

t_error	var_split(const char *src, char **dst_name, char **dst_value);

/* ************************************************************************* */
/*                                   CORE                                    */
/* ************************************************************************* */

t_error	var_set(t_var_list *variables, const char *name, const char *value);
t_error	var_set_export(t_var_list *variables, const char *name, bool export);
t_error	var_set_readonly(t_var_list *variables, const char *name);
t_error	var_get(t_var_list *variables, const char *var_name, t_var **dst_var);
t_error	var_unset(t_var_list *variables, const char *var_name);

#endif
