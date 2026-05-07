#ifndef EXPORT_PRIV_H
# define EXPORT_PRIV_H

# include "variable.h"

t_error	export_add(t_var_list *variables, const char *string);
t_error	export_print(const t_var_list *variables);
t_error	export_build_envp(const t_var_list *variables, char ***dst_envp);

#endif
