/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_walk_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:23:46 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 21:02:53 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "walker.h"
#include "redirector.h"
#include "env.h"

static inline t_error	walk_function_add_positional(
							t_positionals *positionals,
							t_vector *argv,
							size_t i)
{
	const char	*arg;
	t_string	param;

	arg = ((const char **)argv->data)[i];
	if (!string_init(&param, 0, arg, -1))
		return (error_sys());
	if (!vector_push(positionals, &param))
		return (error_sys());
	return (error(ERR_NO));
}

static inline t_error	walk_function_update_positionals(t_cmd *cmd)
{
	t_positionals	positionals;
	size_t			i;
	t_error			err;

	if (!vector_init(&positionals, sizeof(t_string), (size_t)cmd->argc))
		return (error_sys());
	i = 1;
	err = error(ERR_NO);
	while (i < cmd->argv.len - 1)
	{
		err = walk_function_add_positional(&positionals, &cmd->argv, i);
		if (err.type)
			break ;
		i++;
	}
	if (err.type == ERR_NO)
		err = env_push_positionals(&positionals);
	if (err.type)
		vector_free(&positionals, string_free_void);
	return (err);
}

t_error	walk_function(t_cmd *cmd, t_runner *runner, int *status)
{
	t_function	*function;
	t_error		err;

	function = cmd->entry.data.function;
	err = walk_function_update_positionals(cmd);
	if (err.type)
		return (err);
	err = redirect_start(&function->redirs, status);
	if (err.type)
		return (error_priorize(err, env_pop_positionals()));
	err = walk_command(runner, &function->body, status);
	if (err.type == ERR_RETURN)
		err.type = ERR_NO;
	err = error_priorize(err, redirect_stop());
	err = error_priorize(err, env_pop_positionals());
	env_stop_function(&function);
	return (err);
}
