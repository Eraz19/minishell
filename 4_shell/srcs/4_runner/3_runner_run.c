/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_runner_run.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:24:00 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:24:01 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "runner.h"
#include "runner_priv.h"
#include "walker.h"
#include "env.h"
#include "parser.h"
#include "sig.h"
#include <stdbool.h>

static inline t_error	runner_loop_cycle(t_runner *runner)
{
	bool	no_exec;
	t_error	err;

	err = sig_process();
	if (err.type == ERR_NO)
		err = parser_get_ast(&runner->parser, &runner->ast_root);
	if (err.type == ERR_NO)
		err = sig_process();
	if (err.type == ERR_NO)
		err = option_is_active(OPT_NOEXEC, &no_exec);
	if (err.type == ERR_NO && no_exec == false)
		err = walk(runner, &runner->ast_root);
	if (err.type == ERR_NO)
		err = sig_process();
	return (error_priorize(err, env_reap()));
}

/*
Non-fatal errors must be handled in walkers.
Therefore, only fatal errors should bubble up to the main loop.
*/
t_error	runner_run(t_runner *runner)
{
	t_error		err;

	err.type = ERR_NO;
	while (err.type == ERR_NO)
	{
		runner->control_depth = 0;
		runner->loop_depth = 0;
		err = runner_loop_cycle(runner);
		runner_handle_error(runner, &err);
		ast_root_free(&runner->ast_root);
	}
	return (err);
}

t_error	runner_run_ast(t_runner *runner, t_ast_root *ast_root)
{
	bool	no_exec;
	t_error	err;

	runner->control_depth = 0;
	runner->loop_depth = 0;
	err = sig_process();
	if (err.type == ERR_NO)
		err = option_is_active(OPT_NOEXEC, &no_exec);
	if (err.type == ERR_NO && no_exec == false)
		err = walk(runner, ast_root);
	if (err.type == ERR_NO)
		err = sig_process();
	err = error_priorize(err, env_reap());
	runner_handle_error(runner, &err);
	return (err);
}
