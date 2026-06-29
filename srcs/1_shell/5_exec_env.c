#include "error.h"
#include "params.h"
#include <stdlib.h>
# include "logs.h"		// DEBUG
# include <assert.h>	// DEBUG

#define ENV_NAME	"ENV"

// TODO
t_error	shell_exec_env(void)
{
	bool		is_interactive;
	bool		read_from_stdin;
	t_string	raw_env;
	t_error		err;

	print_title("shell_exec_env()");
	err = option_is_active(OPT_INTERACTIVE, &is_interactive);
	if (err.type)
		return (err);
	if (is_interactive == false)
	{
		print_warn("non-interactive mode => skipping ENV execution\n");
		print_result("shell_exec_env()");
		return (error(ERR_NO));
	}
	err = params_get_from_const(ENV_NAME, &raw_env);
	if (err.type != ERR_NO && err.type != ERR_VAR_NOT_FOUND)
		return (error_print(error_sys(), "internal error", NULL, NULL));
	if (!raw_env.data)
	{
		print_warn("no ENV file to execute => skipping.\n");
		print_result("shell_exec_env()");
		return (error(ERR_NO));
	}
	err = option_is_active(OPT_STDIN_INPUT, &read_from_stdin);
	if (err.type)
		return (string_free(&raw_env), err);
	if (read_from_stdin == true)
	{
		print_warn("Expander and Runner not implemented yet => skipping ENV execution\n");
		// TODO: expand ENV
		// TODO: exec ENV
	}
	else
		print_warn("OPT_STDIN_INPUT is not active => skipping ENV execution\n");
	print_result("shell_exec_env()");
	return (string_free(&raw_env), error(ERR_NO));
}
