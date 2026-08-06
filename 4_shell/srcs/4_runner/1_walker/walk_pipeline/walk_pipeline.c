/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walk_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:23:21 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:26:08 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "walker_priv.h"
#include "walk_pipeline_priv.h"
#include "env.h"
#include <assert.h>	// DEBUG
#ifdef DEBUG_CMD
# include <stdio.h>		// DEBUG
# include "logs.h"		// DEBUG
#endif

t_error	walk_pipeline(
			t_runner *runner,
			t_ast_pipeline *pipeline,
			int *exit_status)
{
	bool	old_errexit_ignored;
	t_error	err;

	assert(pipeline->commands.len > 0);
	*exit_status = -1;
	old_errexit_ignored = runner->errexit_ignored;
	if (pipeline->negated == true)
		runner->errexit_ignored = true;
	if (pipeline->commands.len == 1)
		err = walk_pipe_single_command(runner, pipeline, exit_status);
	else
		err = walk_pipe_multiple_commands(runner, pipeline, exit_status);
	if (*exit_status < 0)
		*exit_status = (int)err.type;
#ifdef DEBUG_CMD
	fprintf(stderr, "%s[WALKER] $? = %i%s\n", YELLOW, *exit_status, NC);
#endif
	env_set_last_status(*exit_status);
	runner->errexit_ignored = old_errexit_ignored;
	return (err);
}
