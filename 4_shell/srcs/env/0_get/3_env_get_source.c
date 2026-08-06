/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_env_get_source.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:14:54 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 22:50:40 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_error	env_get_source(const t_string **source)
{
	t_params	*params;

	params = shell_get_params();
	*source = &params->specials.source;
	return (error(ERR_NO));
}
