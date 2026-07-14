#include "error.h"

t_error	builtin_colon(int argc, char **argv, char **envp, int *exit_status)
{
	(void)argc;
	(void)argv;
	(void)envp;
	*exit_status = 0;
	return (error(ERR_NO));
}
