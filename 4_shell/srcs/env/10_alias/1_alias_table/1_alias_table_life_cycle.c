/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_alias_table_life_cycle.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:14:17 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 15:15:01 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alias_table_internal.h"
#include <stdlib.h>

void	alias_free_value(t_string *value)
{
	string_free(value);
	free(value);
}

void	alias_free_value_void(void *value)
{
	alias_free_value(value);
}

void	alias_table_init(t_alias_table *table)
{
	(void)hashmap_init(table, 0, alias_free_value_void);
}

void	alias_table_clear(t_alias_table *table)
{
	hashmap_clear(table);
}

void	alias_table_free(t_alias_table *table)
{
	hashmap_free(table);
}
