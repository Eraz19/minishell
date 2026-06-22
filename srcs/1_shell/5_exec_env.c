#include "error.h"
#include "params.h"
#include <stdlib.h>
# include "logs.h"	// DEBUG

t_error	shell_exec_env(void)
{
	t_error	err;
	char	*raw_env;

	print_title("shell_exec_env()");
	if (!option_is_active(OPT_INTERACTIVE))
	{
		print_warn("non-interactive mode => skipping ENV execution\n");
		print_result("shell_exec_env()");
		return (error(ERR_NO));
	}
	err = params_get("ENV", &raw_env);
	if (err.type != ERR_NO && err.type != ERR_VAR_NOT_FOUND)
		return (error_print(error_sys(), "internal error", NULL, NULL));
	if (!raw_env)
	{
		print_warn("no ENV file to execute => skipping.\n");
		print_result("shell_exec_env()");
		return (error(ERR_NO));
	}
	if (option_is_active(OPT_STDIN_INPUT))
	{
		print_warn("Expander and Runner not implemented yet => skipping ENV execution\n");
		// TODO: expand ENV
		// TODO: exec ENV
	}
	else
		print_warn("OPT_STDIN_INPUT is not active => skipping ENV execution\n");
	print_result("shell_exec_env()");
	return (error(ERR_NO));
}
