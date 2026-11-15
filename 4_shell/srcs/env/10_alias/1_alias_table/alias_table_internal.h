/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_table_internal.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:14:21 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 15:14:54 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALIAS_TABLE_INTERNAL_H
# define ALIAS_TABLE_INTERNAL_H

# include "libft.h"
# include "error.h"

typedef t_hashmap	t_alias_table;

// life cycle

void	alias_table_init(t_alias_table *table);
void	alias_table_clear(t_alias_table *table);
void	alias_table_free(t_alias_table *table);

// ops

t_error	alias_table_set(
			t_alias_table *table,
			const char *name,
			const char *value);
t_error	alias_table_get(
			const t_alias_table *table,
			const char *name,
			const t_string **out_value);
t_error	alias_table_remove(t_alias_table *table, const char *name);

#endif
