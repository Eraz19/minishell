#include "executor.h"
#include "runner.h"
#include "cmd.h"
#include "cmd_resolver.h"
#include "redirector.h"
#include "cmd_assignator.h"
#include "cmd_searcher.h"
#include "cmd_dispatcher.h"
#include "params.h"

/*
TODO: fix `exec` builtin handling
	La bonne logique est :

	exec sans command operand:
		les redirections doivent devenir permanentes dans le shell

	exec avec command operand:
		ce n’est pas juste "commit redirections"
		le builtin exec tente de remplacer le shell par cette commande

	Donc il faut distinguer :

	exec >file

	et :

	exec ls
	exec ls >file
	Cas 1 — exec sans command operand

	Exemple :

	exec >file

	Flow :

	cmd_resolve => command name = exec, argv = ["exec", NULL]

	redirections:
		redirect_commit()

	cmd_assign:
		assignments persistants car special builtin

	dispatch:
		builtin exec voit qu’il n’a pas de command operand
		exit_status = 0

	finalize:
		ne restore pas les redirections

	Donc ici, ton idée redirect_commit() est correcte.

	Cas 2 — exec avec command operand

	Exemple :

	exec ls >file

	Flow :

	cmd_resolve => command name = exec, argv = ["exec", "ls", NULL]

	redirections:
		redirect_start() temporaire, pas commit global immédiat

	cmd_assign:
		assignments persistants car special builtin

	dispatch:
		builtin exec tente d’exécuter "ls" en remplaçant le shell courant

	Si le execve() réussit :

	le process shell est remplacé
	donc aucun restore / cleanup ne se produit

	Si le execve() échoue :

	builtin exec retourne un status non-zero
	finalize restore les redirections temporaires
	shell continue ou exit selon mode / politique POSIX

	Donc pour l’orchestrator, la condition n’est pas :

	cmd->builtin == builtin_exec

	mais plutôt :

	cmd est builtin_exec ET exec n’a pas de command operand

	Avec ton argv.len qui inclut le NULL :

	argv = ["exec", NULL]       => argv.len == 2 => exec sans command operand
	argv = ["exec", "ls", NULL] => argv.len == 3 => exec avec command operand

	Donc conceptuellement :

	if builtin_exec && argv.len == 2:
		redirect_commit()
	else:
		redirect_start()

	Et pareil pour cmd_redirect_stop() :

	if builtin_exec && argv.len == 2:
		pas de restore
	else:
		redirect_stop()
	Point important

	Le builtin exec avec command operand ne doit pas passer par cmd_search() de l’orchestrator actuel, parce que le command name de la simple_command est exec, pas ls.

	Donc c’est le builtin exec lui-même qui devra faire :

	prendre argv[1] comme command name à exécuter
	chercher dans PATH si pas de '/'
	construire argv pour la commande cible = &argv[1]
	execve()
	mapper l’échec

	Ça, c’est un TODO du builtin exec, pas du dispatcher générique.
*/

static inline t_error	cmd_redirect_start(
							const t_cmd *cmd,
							t_redirector *redirector,
							t_ast_simple_command *simple_command)
{
	// TODO: cf big TODO at the top of the file
	if (cmd->builtin == builtin_exec)
		return (redirect_commit(redirector, &simple_command->redirs));
	return (redirect_start(redirector, &simple_command->redirs));
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
// TODO: implement
// TODO: requalify error but let runner loop decide if shell must exit or not ?
t_error	cmd_finalize(t_cmd *cmd, t_runner *runner, t_error err, bool redir_applied)
{
	if (err.type && cmd->exit_status == 0)
		cmd->exit_status = (int)err.type;
	if (err.type == ERR_REDIRECTION_OTHER)
	{
		(void)error_print(err, "runner", "executor", NULL, NULL);
		err = error(ERR_NO);
	}
	(void)params_set_last_status(cmd->exit_status);
	if (redir_applied == true)
		(void)cmd_redirect_stop(cmd, &runner->redirector);
	/* ---------- DEBUG (START) ---------- */
	fprintf(stderr, "--------------------------------------------------\n");
	fprintf(stderr, "[EXECUTOR] [%s()] cmd.exit_status = %i\n", __func__, cmd->exit_status);
	t_string saved_status;
	(void)params_get_from_const("?", &saved_status);
	fprintf(stderr, "[EXECUTOR] [%s()] $?              = %s\n", __func__, saved_status.data);
	fprintf(stderr, "[EXECUTOR] [%s()] error           = %s\n", __func__, error_to_string(err));
	fprintf(stderr, "--------------------------------------------------\n");
	/* ---------- DEBUG (END) ---------- */
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
	err = cmd_dispatch(&cmd, runner);
	return (cmd_finalize(&cmd, runner, err, true));
}
