#include "walker_priv.h"
#include "cmd.h"
#include "redirector.h"
#include "xtrace.h"

static inline t_error	walk_simple_cmd_exec(
							t_cmd *cmd,
							t_runner *runner,
							bool path_is_temporary,
							int *status)
{
	t_cmd_type	type;
	t_error		err;

	type = cmd->entry.type;
	if (type == CMD_NONE || type == CMD_BUILTIN || type == CMD_EXTERNAL)
	{
		err = cmd_execute(cmd, path_is_temporary, status);
		cmd_free(cmd);
		return (error_priorize(err, redirect_stop()));
	}
	else if (type == CMD_SPECIAL_BUILTIN)
		err = cmd->entry.data.special_builtin(cmd->argc, cmd->argv.data, runner, status);
	else
		err = walk_function(cmd, runner, status);
	err = error_priorize(err, redirect_stop());
	return (cmd_finalize_and_free(cmd, err, status));
}

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
	if (err.type == ERR_NO)
		return (walk_simple_cmd_exec(&cmd, runner, path_is_temporary, status));
	err = error_priorize(err, redirect_stop());
	return (cmd_finalize_and_free(&cmd, err, status));
}
