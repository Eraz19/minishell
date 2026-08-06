/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_error_is_flow_control.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 19:53:50 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 19:53:54 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

bool	error_is_flow_control(t_error err)
{
	return (err.type >= ERR_VEOF && err.type <= ERR_INTERRUPTED);
}
