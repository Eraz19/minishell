/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_env_build_envp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:14:54 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 22:50:23 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_error	env_build_envp(t_vector *dst_envp)
{
	t_params	*params;

	params = shell_get_params();
	return (var_build_envp(&params->variables, dst_envp));
}
