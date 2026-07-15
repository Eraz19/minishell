#include "cmd_searcher_priv.h"
#include "builtins.h"
#include "cmd_type.h"
# include "logs.h"	// DEBUG

void	cmd_try_regular_builtin(t_cmd *cmd)
{
	if (str_cmp(cmd->path.data, "/bin/echo") == 0)
		cmd->builtin = builtin_echo;
	else if (str_cmp(cmd->path.data, "/usr/bin/env") == 0)
		cmd->builtin = builtin_env;
	else if (str_cmp(cmd->path.data, "/bin/pwd") == 0
		|| str_cmp(cmd->path.data, "/usr/bin/pwd") == 0)
		cmd->builtin = builtin_pwd;
	else
		return ;
	fprintf(stderr, "%s[RESOLVER] regular builtin matched: '%s%s%s'%s\n",
		YELLOW, BLUE, cmd->path.data, YELLOW, NC);
	cmd->type = CMD_BUILTIN;
	string_free(&cmd->path);
}
