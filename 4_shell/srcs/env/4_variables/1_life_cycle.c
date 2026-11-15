/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_life_cycle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:11:02 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 22:41:06 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "variables.h"
#include "variables_priv.h"
#include "var_load_envp.h"
#include "var_load_mandatory.h"
#include "var_load_up.h"
#include <stdlib.h>

void	var_free_one(void *var)
{
	t_var	*var_casted;

	var_casted = (t_var *)var;
	string_free(&var_casted->value);
	var_casted->export = false;
	var_casted->readonly = false;
	free(var);
}

void	var_init(t_var_list *variables)
{
	(void)hashmap_init(variables, 0, var_free_one);
}

t_error	var_load(t_var_list *variables, char **envp)
{
	t_error	err;

	(void)variables;
	err = var_load_envp(envp);
	if (err.type != ERR_NO)
		return (err);
	err = var_load_mandatory();
	if (err.type != ERR_NO)
		return (err);
	err = var_load_up();
	if (err.type != ERR_NO)
		return (err);
	return (error(ERR_NO));
}

void	var_clear(t_var_list *variables)
{
	hashmap_clear(variables);
}

void	var_free(t_var_list *variables)
{
	hashmap_free(variables);
}
