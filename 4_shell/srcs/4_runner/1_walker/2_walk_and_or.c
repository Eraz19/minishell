/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_walk_and_or.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:23:30 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 22:47:36 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "walker_priv.h"
#include "options.h"

static inline t_error	walk_and_or_pipeline(
							t_runner *runner,
							t_ast_and_or *and_or,
							size_t i,
							int *exit_status)
{
	bool			old_errexit_ignored;
	t_ast_pipeline	*pipeline;
	t_error			err;

	old_errexit_ignored = runner->errexit_ignored;
	if (i < and_or->pipelines.len - 1)
		runner->errexit_ignored = true;
	pipeline = &((t_ast_pipeline *)and_or->pipelines.data)[i];
	err = walk_pipeline(runner, pipeline, exit_status);
	runner->errexit_ignored = old_errexit_ignored;
	return (err);
}

static inline t_error	walk_and_or_check_errexit(
							t_runner *runner,
							t_ast_and_or *and_or,
							size_t i,
							int status)
{
	bool			errexit_is_active;
	t_ast_pipeline	*pipeline;
	t_error			err;

	if (i < and_or->pipelines.len - 1 || runner->errexit_ignored == true)
		return (error(ERR_NO));
	pipeline = &((t_ast_pipeline *)and_or->pipelines.data)[i];
	if (pipeline->negated == true)
		return (error(ERR_NO));
	err = option_is_active(OPT_ERREXIT, &errexit_is_active);
	if (err.type == ERR_NO && errexit_is_active == true && status != 0)
		return (error(ERR_EXIT));
	return (err);
}

static inline size_t	walk_and_or_next_index(
							t_ast_and_or *and_or,
							size_t i,
							int exit_status)
{
	bool	next_on_success;

	while (i < and_or->next_on_success.len)
	{
		next_on_success = ((bool *)and_or->next_on_success.data)[i];
		i++;
		if (next_on_success == true && exit_status == 0)
			return (i);
		else if (next_on_success == false && exit_status != 0)
			return (i);
	}
	return (and_or->pipelines.len);
}

t_error	walk_and_or(t_runner *runner, t_ast_and_or *and_or, int *exit_status)
{
	size_t	i;
	t_error	err;

	i = 0;
	err = error(ERR_NO);
	while (i < and_or->pipelines.len)
	{
		err = walk_and_or_pipeline(runner, and_or, i, exit_status);
		if (err.type == ERR_NO)
			err = walk_and_or_check_errexit(runner, and_or, i, *exit_status);
		if (err.type)
			break ;
		i = walk_and_or_next_index(and_or, i, *exit_status);
	}
	return (err);
}
