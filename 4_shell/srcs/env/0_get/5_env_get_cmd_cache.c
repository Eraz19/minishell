/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_env_get_cmd_cache.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:14:54 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 22:50:48 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_error	env_get_cmd_cache(t_cmd_cache **out_cmd_cache_ptr)
{
	t_params	*params;

	params = shell_get_params();
	*out_cmd_cache_ptr = &params->cmd_cache;
	return (error(ERR_NO));
}
