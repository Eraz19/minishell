/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_is_readonly.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:14:59 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:15:00 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "shell.h"
#include "variables.h"

t_error	env_is_readonly(const char *name, bool *out_is_readonly)
{
	t_params	*params;

	params = shell_get_params();
	if (!params)
		return (error(ERR_SHELL_NOT_FOUND));
	*out_is_readonly = var_is_readonly(&params->variables, name);
	return (error(ERR_NO));
}
