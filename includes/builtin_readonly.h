#ifndef BUILTIN_READONLY_H
# define BUILTIN_READONLY_H

# include <variable.h>

t_error	readonly(t_var_list *variables, const char *name);
t_error	readonly_print(const t_var_list *variables);

#endif
