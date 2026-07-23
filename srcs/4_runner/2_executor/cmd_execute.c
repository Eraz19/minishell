#include "executor.h"
#include "cmd.h"
#include "cmd_resolver.h"
#include "redirector.h"
#include "cmd_assignator.h"
#include "cmd_searcher.h"
#include "cmd_dispatcher.h"
#include "xtrace.h"
#include "sig.h"
#include "options.h"
# include <stdio.h>	// DEBUG
# include "logs.h"	// DEBUG
# include "debug.h"	// DEBUG

static inline t_error	cmd_redirect_start(
							t_cmd *cmd,
							const t_ast_scmd *s_cmd)
{
	t_error	err;

	if (cmd->special_builtin == builtin_exec)
		err = redirect_commit(&s_cmd->redirs, &cmd->exit_status);
	else
		err = redirect_start( &s_cmd->redirs, &cmd->exit_status);
	return (err);
}

static inline t_error	cmd_search_(t_cmd *cmd, t_cmd_cache *cache)
{
	if (cmd->path_is_temporary == true)
		return (cmd_search(cmd, NULL));
	return (cmd_search(cmd, cache));
}

static inline t_error	cmd_requalify_error(t_cmd *cmd, t_error err)
{
	bool	interactive;
	int		signo;
	t_error	option_err;

	(void)error_print(err, NULL, NULL);
	if (err.type == ERR_INTERRUPTED)
	{
		if (sig_has_pending_trap(&signo))
			cmd->exit_status = ERR_POSIX_SIGNAL_BASE_CODE + signo;
		err.type = ERR_NO;
	}
	else if (err.type == ERR_REDIRECTION && cmd->type != CMD_SPECIAL_BUILTIN)
		err.type = ERR_NO;
	else if (err.type == ERR_POSIX_CMD_NOT_FOUND || err.type == ERR_POSIX_CMD_NOT_EXECUTABLE)
		err.type = ERR_NO;
	else if (err.type > ERR_POSIX_SYNTAX && err.type < ERR_POSIX_READ)
	{
		option_err = option_is_active(OPT_INTERACTIVE, &interactive);
		if (option_err.type)
			err = error_priorize(err, option_err);
		else if (interactive == true)
			err.type = ERR_NO;
	}
	return (err);
}

t_error	cmd_finalize(t_cmd *cmd, t_error err, bool redir_applied, int *exit_status)
{
	int		initial_cmd_status;		// DEBUG
	int		initial_exit_status;	// DEBUG
	t_error	initial_error;			// DEBUG

	initial_cmd_status = cmd->exit_status;
	initial_exit_status = *exit_status;
	initial_error = err;
	if (cmd->exit_status < 0)
		cmd->exit_status = (int)err.type;
	if (err.type && error_is_flow_control(err) == false)
		err = cmd_requalify_error(cmd, err);
	if (redir_applied == true)
		err = error_priorize(err, redirect_stop());
	// if (err.type && error_is_flow_control(err) == false && cmd->exit_status <= 0)
	// 	cmd->exit_status = (int)err.type;
	*exit_status = cmd->exit_status;
	fprintf(stderr, MAGENTA "##################################################\n" NC);
	/* ---------- DEBUG (START) ---------- */
	fprintf(stderr, "[CMD   ] type        => %s\n", cmd_type_to_string(cmd->type));
	fprintf(stderr, "[CMD   ] exit_status => %i => %i => %i\n", initial_exit_status, initial_cmd_status, *exit_status);
	fprintf(stderr, "[CMD   ] error       = %s => %s\n", error_to_string(initial_error), error_to_string(err));
	/* ---------- DEBUG (END) ---------- */
	sig_process();
	cmd_free(cmd);
	return (err);
}

t_error cmd_execute(t_runner *runner, const t_ast_scmd *simple_command, int *exit_status)
{
	t_cmd	cmd;
	t_error	err;

	fprintf(stderr, MAGENTA "###################### OUT #######################\n" NC);
	cmd_init(&cmd);
	err = cmd_resolve(&cmd, &simple_command->words);
	if (err.type == ERR_NO)
		err = cmd_redirect_start(&cmd, simple_command);
	if (err.type)
		return (cmd_finalize(&cmd, err, false, exit_status));
	err = cmd_assign(&cmd, &simple_command->assignments);
	if (err.type)
		return (cmd_finalize(&cmd, err, true, exit_status));
	err = xtrace_print_argv(&cmd.argv);
	if (err.type)
		return (cmd_finalize(&cmd, err, true, exit_status));
	if (cmd.type == CMD_EXTERNAL)
	{
		err = cmd_search_(&cmd, runner->cmd_cache);
		if (err.type)
			return (cmd_finalize(&cmd, err, true, exit_status));
	}
	err = cmd_dispatch(&cmd, runner);
	return (cmd_finalize(&cmd, err, true, exit_status));
}
