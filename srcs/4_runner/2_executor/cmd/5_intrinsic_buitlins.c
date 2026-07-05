#include "libft.h"
#include "cmd_priv.h"
#include "builtins.h"

static inline bool	cmd_name_is_intrinsic_builtin2(
						const char *name,
						t_builtin *out_builtin)
{
	if (str_cmp(name, "type") == 0)
		return (*out_builtin = builtin_type, true);
	else if (str_cmp(name, "ulimit") == 0)
		return (*out_builtin = builtin_ulimit, true);
	else if (str_cmp(name, "umask") == 0)
		return (*out_builtin = builtin_umask, true);
	else if (str_cmp(name, "unalias") == 0)
		return (*out_builtin = builtin_unalias, true);
	else if (str_cmp(name, "wait") == 0)
		return (*out_builtin = builtin_wait, true);
	return (*out_builtin = NULL, false);
}

bool	cmd_name_is_intrinsic_builtin(const char *name, t_builtin *out_builtin)
{
	if (str_cmp(name, "alias") == 0)
		return (*out_builtin = builtin_alias, true);
	else if (str_cmp(name, "bg") == 0)
		return (*out_builtin = builtin_bg, true);
	else if (str_cmp(name, "cd") == 0)
		return (*out_builtin = builtin_cd, true);
	else if (str_cmp(name, "command") == 0)
		return (*out_builtin = builtin_command, true);
	else if (str_cmp(name, "fc") == 0)
		return (*out_builtin = builtin_fc, true);
	else if (str_cmp(name, "fg") == 0)
		return (*out_builtin = builtin_fg, true);
	else if (str_cmp(name, "getopts") == 0)
		return (*out_builtin = builtin_getopts, true);
	else if (str_cmp(name, "hash") == 0)
		return (*out_builtin = builtin_hash, true);
	else if (str_cmp(name, "jobs") == 0)
		return (*out_builtin = builtin_jobs, true);
	else if (str_cmp(name, "kill") == 0)
		return (*out_builtin = builtin_kill, true);
	else if (str_cmp(name, "read") == 0)
		return (*out_builtin = builtin_read, true);
	else
		return (cmd_name_is_intrinsic_builtin2(name, out_builtin));
}
