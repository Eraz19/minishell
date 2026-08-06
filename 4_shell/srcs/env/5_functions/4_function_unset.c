/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_function_unset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:11:37 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:11:38 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions_priv.h"

void	function_unset(t_functions *functions, const char *name)
{
	t_function	*function;

	function = hashmap_get(functions, name);
	if (function == NULL)
		return ;
	hashmap_remove(functions, name);
	function->pending_free = true;
	if (function->active_count == 0)
		function_free(&function);
}
