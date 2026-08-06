/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_env_get_last_status.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:14:54 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 22:50:45 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_error	env_get_last_status(int *out)
{
	t_params	*params;

	params = shell_get_params();
	*out = env_get_last_status_from(params);
	return (error(ERR_NO));
}

int	env_get_last_status_from(t_params *params)
{
	return (params->specials.last_status);
}
