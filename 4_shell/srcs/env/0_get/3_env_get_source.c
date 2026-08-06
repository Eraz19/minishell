/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_env_get_source.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:14:54 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 17:25:39 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <assert.h>	// DEBUG

t_error	env_get_source(const t_string **source)
{
	t_params	*params;

	params = shell_get_params();
	assert(params != NULL);
	*source = &params->specials.source;
	return (error(ERR_NO));
}
