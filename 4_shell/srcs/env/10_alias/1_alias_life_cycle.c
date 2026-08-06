/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_alias_life_cycle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:14:41 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 16:50:45 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alias.h"

void	alias_init(t_alias *alias)
{
	alias_table_init(&alias->table);
	alias_stack_init(&alias->stack);
}

void	alias_clear_stack(t_alias *alias)
{
	alias_stack_clear(&alias->stack);
}

void	alias_clear(t_alias *alias)
{
	alias_table_clear(&alias->table);
	alias_stack_clear(&alias->stack);
}

void	alias_free(t_alias *alias)
{
	alias_table_free(&alias->table);
	alias_stack_free(&alias->stack);
}
