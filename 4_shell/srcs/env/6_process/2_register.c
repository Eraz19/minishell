/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_register.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:11:48 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:11:49 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

t_error	process_register(t_process_table *table, pid_t pid)
{
	t_process	process;

	process.pid = pid;
	process.status = -1;
	if (!vector_push(table, &process))
		return (error_sys());
	return (error(ERR_NO));
}
