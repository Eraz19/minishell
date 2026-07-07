#ifndef CMD_RESOLVER_PRIV_H
# define CMD_RESOLVER_PRIV_H

# include "cmd_resolution_type.h"
# include "builtins.h"
# include "functions.h"
# include <stdbool.h>

void	cmd_resolution_init(t_cmd_resolution *cmd_resolution);
void	cmd_resolution_free(t_cmd_resolution *cmd_resolution);
bool	cmd_name_is_special_builtin(const char *name, t_builtin *out_builtin);
bool	cmd_name_is_unspecified(const char *name);
bool	cmd_name_is_function(
			t_functions *functions,
			const char *name,
			const t_function **out_function);
bool	cmd_name_is_intrinsic_builtin(const char *name, t_builtin *out_builtin);
bool	cmd_name_is_regular_builtin(const char *name, t_builtin *out_builtin);

#endif
