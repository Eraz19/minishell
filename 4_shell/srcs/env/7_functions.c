/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_functions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:15:03 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:15:04 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "shell.h"

t_error	env_set_function(t_ast_function_def *function_def)
{
	t_params	*params;

	params = shell_get_params();
	if (params == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	return (function_set(&params->functions, function_def));
}

t_error	env_get_function(const char *name, t_function **out)
{
	t_params	*params;

	params = shell_get_params();
	if (params == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	return (function_get(&params->functions, name, out));
}

t_error	env_unset_function(const char *name)
{
	t_params	*params;

	params = shell_get_params();
	if (params == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	function_unset(&params->functions, name);
	return (error(ERR_NO));
}

void	env_stop_function(t_function **function)
{
	function_stop(function);
}
