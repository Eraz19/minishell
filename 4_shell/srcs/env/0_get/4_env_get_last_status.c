/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_env_get_last_status.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:14:54 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 17:26:01 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <assert.h>	// DEBUG

t_error	env_get_last_status(int *out)
{
	t_params	*params;

	params = shell_get_params();
	assert(params != NULL);
	*out = env_get_last_status_from(params);
	return (error(ERR_NO));
}

int	env_get_last_status_from(t_params *params)
{
	return (params->specials.last_status);
}
