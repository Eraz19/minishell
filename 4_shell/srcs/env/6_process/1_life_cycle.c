/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_life_cycle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:11:46 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:11:47 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

void	process_init(t_process_table *table)
{
	(void)vector_init(table, sizeof(t_process), 0);
}

void	process_clear(t_process_table *table)
{
	table->len = 0;
}

void	process_free(t_process_table *table)
{
	vector_free(table, NULL);
}
