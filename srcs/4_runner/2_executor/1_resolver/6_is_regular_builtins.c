#include "libft.h"
#include "cmd_resolver_priv.h"
#include "builtins.h"

bool	cmd_name_is_regular_builtin(const char *name, t_builtin *out_builtin)
{
	if (str_cmp(name, "echo") == 0)
		return (*out_builtin = builtin_echo, true);
	else if (str_cmp(name, "env") == 0)
		return (*out_builtin = builtin_env, true);
	else if (str_cmp(name, "pwd") == 0)
		return (*out_builtin = builtin_pwd, true);
	return (*out_builtin = NULL, false);
}
