#ifndef VARIABLE_PRIV_H
# define VARIABLE_PRIV_H

# include "variable.h"

// ⚠️ POSIX: names shall be checked depending on current locale at shell startup.
// ⚠️ POSIX: modifying the locale while shell is running should not affect variables name validation of current shell.
bool	var_name_is_valid(const char *name);
// warning: caller must handle malloc errors (by checking var.name and var.value)
t_var	var_new(const char *name, const char *value, bool export, bool ronly);
t_error	var_update_value(t_var *var, const char *value);
bool	var_find(t_var_list *variables, const char *var_name, size_t *res);

#endif
