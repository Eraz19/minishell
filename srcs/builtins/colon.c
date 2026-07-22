#include "builtins.h"
#include "error.h"

t_error	builtin_colon(int argc, char **argv, t_runner *runner, int *exit_status)
{
	(void)argc;
	(void)argv;
	(void)runner;
	*exit_status = 0;
	return (error(ERR_NO));
}
