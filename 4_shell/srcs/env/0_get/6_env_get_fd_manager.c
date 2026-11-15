/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_env_get_fd_manager.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:14:54 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 22:50:53 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_error	env_get_fd_manager(t_fd_manager **out_fd_manager_ptr)
{
	t_params	*params;

	params = shell_get_params();
	*out_fd_manager_ptr = &params->fd_manager;
	return (error(ERR_NO));
}
