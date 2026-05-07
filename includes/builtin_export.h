#ifndef BUILTIN_EXPORT_H
# define BUILTIN_EXPORT_H

# include "variable.h"

t_error	export(t_var_list *variables, const char *name);
t_error	export_print(const t_var_list *variables);
t_error	export_build_envp(const t_var_list *variables, char ***dst_envp);

#endif
