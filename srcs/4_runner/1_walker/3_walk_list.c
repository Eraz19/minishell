#include "error.h"
#include "walker_priv.h"
#include "shell.h"
#include "posix_helpers.h"
#include <unistd.h>
#include <stdlib.h>
# include <assert.h>

/*
après chaque and_or exécuté :
    si -e actif
    && errexit_ignored == 0
    && status != 0
    && dernier pipeline exécuté non negated
        quitter l’environnement courant
*/

static inline t_error	walk_and_or_async(
							t_runner *runner,
							t_ast_and_or *and_or,
							int *exit_status)
{
	pid_t	pid;
	int		status;
	t_error	err;

	pid = fork();
	if (pid < 0)
		return (error_sys());
	else if (pid == 0)
	{
		err = shell_init_subshell(SUBSHELL_ASYNC_AND_OR);
		if (err.type == ERR_NO)
			err = walk_and_or(runner, and_or, exit_status);
		status = *exit_status;
		shell_free_void();
		exit(status);
	}
	err = params_register_process(pid);
	*exit_status = 0;
	return (err);
}

static inline t_error	walk_list_priv(
							t_runner *runner,
							t_ast_list *list,
							int *exit_status)
{
	size_t			i;
	t_ast_and_or	*and_or;
	bool			async;
	t_error			err;

	assert(list->and_ors.len > 0);
	assert(list->asyncs.len == list->and_ors.len);
	i = 0;
	while (i < list->and_ors.len)
	{
		and_or = &((t_ast_and_or *)list->and_ors.data)[i];
		async = ((bool *)list->asyncs.data)[i];
		if (async == true)
			err = walk_and_or_async(runner, and_or, exit_status);
		else
			err = walk_and_or(runner, and_or, exit_status);
		if (err.type)
			break ;
		i++;
	}
	return (err);
}

static inline t_error	walk_list_in_subshell(
							t_runner *runner,
							t_ast_list *list,
							int *exit_status)
{
	pid_t	pid;
	int		status;
	t_error	err;

	pid = fork();
	if (pid < 0)
		return (error_sys());
	else if (pid == 0)
	{
		err = shell_init_subshell(SUBSHELL_NORMAL);
		if (err.type == ERR_NO)
			err = walk_list_priv(runner, list, exit_status);
		status = *exit_status;
		shell_free_void();
		exit(status);
	}
	return (posix_wait_and_retry(pid, exit_status));
}

t_error	walk_list(t_runner *runner, t_ast_list *list, int *exit_status)
{
	if (list->and_ors.len == 0)
	{
		*exit_status = 0;
		return (error(ERR_NO));
	}
	if (list->subshell == false)
		return (walk_list_priv(runner, list, exit_status));
	else
		return (walk_list_in_subshell(runner, list, exit_status));
}
