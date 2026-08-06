/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_is_readonly.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:11:13 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:11:14 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "variables.h"
#include "variables_priv.h"

bool	var_is_readonly(const t_var_list *variables, const char *name)
{
	const t_var	*var;

	var = hashmap_get_const(variables, name);
	return (var != NULL && var->readonly);
}
