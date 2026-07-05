#include "libft.h"
#include "cmd_priv.h"
#include "builtins.h"

static inline bool	cmd_name_is_special_builtin2(
						const char *name,
						t_builtin *out_builtin)
{
	if (str_cmp(name, "shift") == 0)
		return (*out_builtin = builtin_shift, true);
	else if (str_cmp(name, "times") == 0)
		return (*out_builtin = builtin_times, true);
	else if (str_cmp(name, "trap") == 0)
		return (*out_builtin = builtin_trap, true);
	else if (str_cmp(name, "unset") == 0)
		return (*out_builtin = builtin_unset, true);
	return (*out_builtin = NULL, false);
}

bool	cmd_name_is_special_builtin(const char *name, t_builtin *out_builtin)
{
	if (str_cmp(name, "break") == 0)
		return (*out_builtin = builtin_break, true);
	else if (str_cmp(name, ":") == 0)
		return (*out_builtin = builtin_colon, true);
	else if (str_cmp(name, "continue") == 0)
		return (*out_builtin = builtin_continue, true);
	else if (str_cmp(name, "dot") == 0)
		return (*out_builtin = builtin_dot, true);
	else if (str_cmp(name, "eval") == 0)
		return (*out_builtin = builtin_eval, true);
	else if (str_cmp(name, "exec") == 0)
		return (*out_builtin = builtin_exec, true);
	else if (str_cmp(name, "exit") == 0)
		return (*out_builtin = builtin_exit, true);
	else if (str_cmp(name, "export") == 0)
		return (*out_builtin = builtin_export, true);
	else if (str_cmp(name, "readonly") == 0)
		return (*out_builtin = builtin_readonly, true);
	else if (str_cmp(name, "return") == 0)
		return (*out_builtin = builtin_return, true);
	else if (str_cmp(name, "set") == 0)
		return (*out_builtin = builtin_set, true);
	else
		return (cmd_name_is_special_builtin2(name, out_builtin));
}
