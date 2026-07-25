#include "walker_priv.h"
#include "cmd.h"
#include "redirector.h"
#include "xtrace.h"

t_error	walk_simple_cmd(t_runner *runner, t_ast_scmd *command, int *status)
{
	t_cmd	cmd;
	bool	path_is_temporary;
	t_error	err;

	cmd_init(&cmd);
	err = cmd_resolve(&cmd, &command->words, status);
	if (err.type == ERR_NO)
		err = redirect_start(&command->redirs, status);
	if (err.type)
		return (cmd_finalize_and_free(&cmd, err, status));
	err = cmd_assign(&cmd, &command->assignments, &path_is_temporary, status);
	if (err.type == ERR_NO)
		err = xtrace_print_argv(&cmd.argv);
	else if (err.type == ERR_NO && cmd.entry.type == CMD_SPECIAL_BUILTIN)
		err = cmd.entry.data.special_builtin(cmd.argc, cmd.argv.data, runner, status);
	else if (err.type == ERR_NO && cmd.entry.type == CMD_FUNCTION)
		err = walk_function(&cmd, runner, status);
	if (err.type == ERR_NO)
		err = cmd_execute(&cmd, path_is_temporary, status);
	err = error_priorize(err, redirect_stop());
	return (cmd_finalize_and_free(&cmd, err, status));
}
