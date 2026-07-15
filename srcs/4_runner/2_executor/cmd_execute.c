#include "executor.h"
#include "cmd.h"
#include "cmd_resolver.h"
#include "redirector.h"
#include "cmd_assignator.h"
#include "cmd_searcher.h"
#include "cmd_dispatcher.h"

static inline t_error	cmd_redirect_start(
							t_cmd *cmd,
							t_redirector *redirector,
							const t_ast_scmd *s_cmd)
{
	t_error	err;

	// TODO: cf big TODO at the top of the file
	if (cmd->builtin == builtin_exec)
		err = redirect_commit(redirector, &s_cmd->redirs, &cmd->exit_status);
	else
		err = redirect_start(redirector, &s_cmd->redirs, &cmd->exit_status);
	if (err.type == ERR_REDIRECTION)
	{
		if (cmd->type == CMD_SPECIAL_BUILTIN)
			err.type = ERR_POSIX_REDIR_SPECIAL;
		else
			err.type = ERR_REDIRECTION_OTHER;
	}
	return (err);
}

static inline t_error	cmd_redirect_stop(t_cmd *cmd, t_redirector *redirector)
{
	// TODO: cf big TODO at the top of the file
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

# include <stdio.h>
t_error	cmd_finalize(t_cmd *cmd, t_runner *runner, t_error err, bool redir_applied, int *exit_status)
{
	if (err.type == ERR_REDIRECTION_OTHER)
	{
		(void)error_print(err, "runner", "executor", NULL, NULL);
		if (cmd->exit_status < 0)
			cmd->exit_status = (int)err.type;
		err = error(ERR_NO);
	}
	if (redir_applied == true)
		err = error_priorize(err, cmd_redirect_stop(cmd, &runner->redirector));
	*exit_status = cmd->exit_status;
	/* ---------- DEBUG (START) ---------- */
	fprintf(stderr, "--------------------------------------------------\n");
	fprintf(stderr, "[CMD   ] [%s()] exit_status = %i\n", __func__, *exit_status);
	fprintf(stderr, "[CMD   ] [%s()] error       = %s\n", __func__, error_to_string(err));
	fprintf(stderr, "--------------------------------------------------\n");
	/* ---------- DEBUG (END) ---------- */
	cmd_free(cmd);
	return (err);
}

t_error cmd_execute(t_runner *runner, const t_ast_scmd *simple_command, int *exit_status)
{
	t_cmd	cmd;
	t_error	err;

	cmd_init(&cmd);
	err = cmd_resolve(&cmd, &simple_command->words);
	if (err.type == ERR_NO)
		err = cmd_redirect_start(&cmd, &runner->redirector, simple_command);
	if (err.type)
		return (cmd_finalize(&cmd, runner, err, false, exit_status));
	err = cmd_assign(&cmd, &simple_command->assignments);
	if (err.type)
		return (cmd_finalize(&cmd, runner, err, true, exit_status));
	if (cmd.type == CMD_EXTERNAL)
	{
		err = cmd_search_(&cmd, &runner->cmd_cache);
		if (err.type)
			return (cmd_finalize(&cmd, runner, err, true, exit_status));
	}
	err = cmd_dispatch(&cmd, runner);
	return (cmd_finalize(&cmd, runner, err, true, exit_status));
}
