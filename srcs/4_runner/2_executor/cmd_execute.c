#include "executor.h"
#include "runner.h"
#include "cmd.h"
#include "cmd_resolver.h"
#include "redirector.h"
#include "cmd_assignator.h"
#include "cmd_searcher.h"
#include "cmd_dispatcher.h"
#include "params.h"

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

// TODO: implement
// TODO: requalify error but let runner loop decide if shell must exit or not
t_error	cmd_finalize(t_cmd *cmd, t_runner *runner, t_error err, bool redir_applied)
{
	(void)params_set_last_status(cmd->exit_status);
	if (redir_applied == true)
		(void)cmd_redirect_stop(cmd, &runner->redirector);
	(void)runner;
	(void)error_print(error(ERR_NOT_IMPLEMENTED), "runner", __func__, NULL, NULL);
	cmd_free(cmd);
	return (err);
}

t_error cmd_execute(t_runner *runner, t_ast_simple_command *simple_command)
{
	t_cmd	cmd;
	t_error	err;

	cmd_init(&cmd);
	err = cmd_resolve(&cmd, &runner->functions, &simple_command->words);
	if (err.type)
		return (cmd_finalize(&cmd, runner, err, false));
	err = cmd_redirect_start(&cmd, &runner->redirector, simple_command);
	if (err.type)
		return (cmd_finalize(&cmd, runner, err, false));
	err = cmd_assign(&cmd, &simple_command->assignments);
	if (err.type)
		return (cmd_finalize(&cmd, runner, err, true));
	if (cmd.type == CMD_EXTERNAL)
	{
		err = cmd_search_(&cmd, &runner->cmd_cache);
		if (err.type)
			return (cmd_finalize(&cmd, runner, err, true));
	}
	cmd_dispatch(&cmd);
	return (cmd_finalize(&cmd, runner, err, true));
}
