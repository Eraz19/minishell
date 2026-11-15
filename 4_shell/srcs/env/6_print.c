/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_print.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:15:01 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 22:50:10 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "shell.h"

t_error	env_print(t_env_print_mode mode)
{
	t_params	*params;

	params = shell_get_params();
	if (mode == ENV_PRINT_ALIAS)
		return (alias_print_all(&params->alias));
	return (var_print((t_var_print_mode)mode));
}

t_error	env_print_one_alias(const char *name)
{
	t_params	*params;

	params = shell_get_params();
	return (alias_print_one(&params->alias, name));
}
