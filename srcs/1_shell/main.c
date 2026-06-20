#include "shell_priv.h"
#include <stdlib.h>
# include "logs.h"	// TODO: tmp debug

// @ret ERR_NO / ERR_LIBC.
static t_error	shell_exec_env(t_shell *shell)
{
	t_error	err;
	char	*raw_env;

	print_title("shell_exec_env()");
	if (!option_is_active_in(shell->params.options, OPT_INTERACTIVE))
		return (error(ERR_NO));
	err = params_get("ENV", &raw_env);
	if (err.type == ERR_LIBC)
		return (err);
	if (!raw_env)
		return (error(ERR_NO));
	if (option_is_active(OPT_STDIN_INPUT))
	{
		print_warn("Expander and Runner not implemented yet => skipping ENV execution\n");
		// TODO: expand ENV
		// TODO: exec ENV
	}
	print_result("shell_exec_env()");
	return (error(ERR_NO));
}

t_error	shell_start(int argc, char **argv, char **envp)
{
	static const char	message[] = ": unable to malloc shell data struct: ";
	t_shell				*shell;
	t_error				err;

	print_start(99, "shell_start()");
	shell = malloc(sizeof(*shell));
	if (!shell)
		return (error_print(error_sys(), message, NULL, NULL));
	print_title("shell_init()");
	shell_init(shell);
	print_result("shell_init()");
	shell_set(shell);
	err = shell_load(shell, argc, argv, envp);
	if (err.type != ERR_NO)
		shell_exit(err);
	err = shell_exec_env(shell);
	if (err.type != ERR_NO)
		return (err);
	/* ---------- TODO (START) ---------- */
	t_ast_node	ast;
	t_ast_node	*ast_ptr = &ast;
	builder_get_ast(&ast_ptr);
	// TODO: runner_run(t_shell *shell);
	/* ---------- TODO (END) ---------- */
	print_warn("Runner not implemented yet => skipping execution loop\n");
	print_stop();
	shell_exit(err);
	return (error(ERR_NO));
}
