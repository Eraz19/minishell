/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_walk_pipe_life_cycle.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:23:07 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:27:12 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "walk_pipeline_priv.h"
#include "options.h"
#include <stdlib.h>

void	walk_pipe_init(
			t_pipe_run *run,
			t_runner *runner,
			t_ast_pipeline *pipeline)
{
	run->runner = runner;
	run->pipeline = pipeline;
	run->command_id = 0;
	run->pipe_fds[READ_ID] = -1;
	run->pipe_fds[WRITE_ID] = -1;
	run->cmd_fds[READ_ID] = -1;
	run->cmd_fds[WRITE_ID] = -1;
	run->last_failure = 0;
	run->pipefail_is_active = false;
	run->pids = NULL;
	run->exit_status = -1;
}

t_error	walk_pipe_spawn(
			t_runner *runner,
			t_ast_pipeline *pipeline,
			t_pipe_run *run)
{
	t_error	err;

	walk_pipe_init(run, runner, pipeline);
	err = option_is_active(OPT_PIPEFAIL, &run->pipefail_is_active);
	if (err.type)
		return (err);
	run->pids = malloc(sizeof(*run->pids) * pipeline->commands.len);
	if (run->pids == NULL)
		return (error_sys());
	ft_bzero(run->pids, pipeline->commands.len * sizeof(*run->pids));
	return (error(ERR_NO));
}

void	walk_pipe_free(t_pipe_run *run)
{
	(void)walk_pipe_close_fd(run, run->pipe_fds[READ_ID]);
	(void)walk_pipe_close_fd(run, run->pipe_fds[WRITE_ID]);
	(void)walk_pipe_close_fd(run, run->cmd_fds[READ_ID]);
	(void)walk_pipe_close_fd(run, run->cmd_fds[WRITE_ID]);
	if (run->pids != NULL)
		free(run->pids);
	walk_pipe_init(run, run->runner, run->pipeline);
}
