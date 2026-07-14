#include "executor.h"
#include "cmd.h"
#include "cmd_resolver.h"
#include "redirector.h"
#include "cmd_assignator.h"
#include "cmd_searcher.h"
#include "cmd_dispatcher.h"

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
							const t_ast_scmd *simple_command)
{
	t_error	err;

	// TODO: cf big TODO at the top of the file
	if (cmd->builtin == builtin_exec)
		err = redirect_commit(redirector, &simple_command->redirs);
	else
		err = redirect_start(redirector, &simple_command->redirs);
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
			cmd->exit_status = (int)ERR_REDIRECTION_OTHER;
		err = error(ERR_NO);
	}
	if (redir_applied == true)
		err = error_priorize(err, cmd_redirect_stop(cmd, &runner->redirector));
	*exit_status = cmd->exit_status;
	/* ---------- DEBUG (START) ---------- */
	fprintf(stderr, "--------------------------------------------------\n");
	fprintf(stderr, "[EXECTR] [%s()] exit_status = %i\n", __func__, *exit_status);
	fprintf(stderr, "[EXECTR] [%s()] error       = %s\n", __func__, error_to_string(err));
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
	if (err.type)
		return (cmd_finalize(&cmd, runner, err, false, exit_status));
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
	err = cmd_dispatch(&cmd, runner, exit_status);
	return (cmd_finalize(&cmd, runner, err, true, exit_status));
}
