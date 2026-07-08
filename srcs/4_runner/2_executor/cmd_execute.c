#include "executor.h"
#include "runner.h"
#include "cmd.h"
#include "cmd_resolver.h"
#include "redirector.h"
#include "cmd_assignator.h"
#include "cmd_searcher.h"

static inline t_error	cmd_redirect_start(
							const t_cmd *cmd,
							t_redirector *redirector,
							t_ast_simple_command *simple_command)
{
	if (cmd->builtin == builtin_exec)
		return (redirect_commit(redirector, &simple_command->redirs));
	return (redirect_start(redirector, &simple_command->redirs));
}

static inline t_error	cmd_redirect_stop(t_cmd *cmd, t_redirector *redirector)
{
	if (cmd->builtin != builtin_exec)
		return (redirect_stop(redirector));
	return (error(ERR_NO));
}

static inline t_error	cmd_search_(t_cmd *cmd, t_cmd_cache *cache)
{
	if (cmd->path_is_temporary == true)
		return (cmd_search(cmd, NULL));
	return (cmd_search(cmd, cache));
}

static inline t_error	cmd_handle_error(
							t_cmd *cmd,
							t_redirector *redirector,
							t_error err)
{
	t_error	redirect_err;

	redirect_err = cmd_redirect_stop(cmd, redirector);
	cmd_free(cmd);
	if (redirect_err.type
		&& (err.type == ERR_VAR_READ_ONLY
		|| err.type == ERR_CMD_NOT_FOUND
		|| err.type == ERR_CMD_NOT_EXECUTABLE))
	{
		(void)error_print(err, NULL, NULL);
		return (redirect_err);
	}
	return (err);
}

t_error cmd_execute(
			t_runner *runner,
			t_ast_simple_command *simple_command,
			int *exit_status)
{
	t_cmd	cmd;
	t_error	err;

	cmd_init(&cmd);
	err = cmd_resolve(&cmd, &runner->functions, &simple_command->words);
	if (err.type)
		return (cmd_free(&cmd), err);
	err = cmd_redirect_start(&cmd, &runner->redirector, simple_command);
	if (err.type)
		return (cmd_free(&cmd), err);
	err = cmd_assign(&cmd, &simple_command->assignments);
	if (err.type == ERR_NO && cmd.type == CMD_EXTERNAL)
		err = cmd_search_(&cmd, &runner->cmd_cache);
	if (err.type)
		return (cmd_handle_error(&cmd, &runner->redirector, err));
	// TODO: execute (fork, close_backups, execve, wait, set $?)
	err = cmd_redirect_stop(&cmd, &runner->redirector);
	cmd_free(&cmd);
	return (err);
}
