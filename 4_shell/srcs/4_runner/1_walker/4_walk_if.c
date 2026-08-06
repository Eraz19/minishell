/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_walk_if.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:23:34 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:23:35 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "walker_priv.h"
#include <assert.h>

static inline t_error	walk_if_condition(
							t_runner *runner,
							t_ast_list *condition,
							int *exit_status)
{
	bool	old_errexit_ignored;
	t_error	err;

	old_errexit_ignored = runner->errexit_ignored;
	runner->errexit_ignored = true;
	err = walk_list(runner, condition, exit_status);
	runner->errexit_ignored = old_errexit_ignored;
	return (err);
}

t_error	walk_if(t_runner *runner, t_ast_if *if_node, int *exit_status)
{
	size_t		i;
	t_ast_list	*condition;
	t_ast_list	*body;
	t_error		err;

	assert(if_node->conditions.len > 0);
	assert(if_node->conditions.len == if_node->bodies.len);
	i = 0;
	while (i < if_node->conditions.len)
	{
		condition = &((t_ast_list *)if_node->conditions.data)[i];
		err = walk_if_condition(runner, condition, exit_status);
		if (err.type)
			return (err);
		else if (*exit_status == 0)
		{
			body = &((t_ast_list *)if_node->bodies.data)[i];
			return (walk_list(runner, body, exit_status));
		}
		i++;
	}
	if (if_node->has_else == true)
		return (walk_list(runner, &if_node->else_body, exit_status));
	*exit_status = 0;
	return (err);
}
