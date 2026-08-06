/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_api.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:14:43 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:14:44 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alias.h"
#include <assert.h>

t_error	alias_set(t_alias *alias, const char *name, const char *value)
{
	assert(alias != NULL);
	assert(name != NULL);
	assert(name[0] != '\0');
	assert(value != NULL);
	return (alias_table_set(&alias->table, name, value));
}

t_error	alias_get(
			t_alias *alias,
			const t_string *name,
			const t_string **out_value)
{
	size_t			i;
	const t_string	*curr_alias;
	t_error			err;

	assert(alias != NULL);
	assert(name != NULL);
	assert(name->data != NULL);
	assert(name->len > 0);
	assert(out_value != NULL);
	i = 0;
	while (i < alias->stack.len)
	{
		curr_alias = &((const t_string *)alias->stack.data)[i];
		if (string_cmp(name, curr_alias) == true)
			return (error(ERR_VAR_NOT_FOUND));
		i++;
	}
	err = alias_table_get(&alias->table, name->data, out_value);
	if (err.type == ERR_NO)
		err = alias_stack_push(&alias->stack, name);
	if (err.type == ERR_NO)
		err = alias_forbidden_set(&alias->forbidden, name->data);
	return (err);
}

bool	alias_is_forbidden(t_alias *alias, const char *name)
{
	assert(alias != NULL);
	assert(name != NULL);
	return (alias_forbidden_contains(&alias->forbidden, name));
}

void	alias_pop_from_stack(t_alias *alias)
{
	assert(alias != NULL);
	alias_stack_pop(&alias->stack);
}

t_error	alias_unset(t_alias *alias, const char *name)
{
	assert(alias != NULL);
	assert(name != NULL);
	return (alias_table_remove(&alias->table, name));
}
