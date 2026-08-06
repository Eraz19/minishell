/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_print.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:15:01 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 21:48:03 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "shell.h"
#include <assert.h>	// DEBUG

t_error	env_print(t_env_print_mode mode)
{
	t_params	*params;

	assert(mode == ENV_PRINT_EXPORT
		|| mode == ENV_PRINT_READONLY
		|| mode == ENV_PRINT_SET
		|| mode == ENV_PRINT_ALIAS);
	params = shell_get_params();
	assert(params != NULL);
	if (mode == ENV_PRINT_ALIAS)
		return (alias_print_all(&params->alias));
	return (var_print((t_var_print_mode)mode));
}

t_error	env_print_one_alias(const char *name)
{
	t_params	*params;

	params = shell_get_params();
	assert(params != NULL);
	return (alias_print_one(&params->alias, name));
}
