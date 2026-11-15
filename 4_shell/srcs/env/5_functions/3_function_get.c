/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_function_get.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:11:35 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:11:36 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"

t_error	function_get(t_functions *functions, const char *name, t_function **out)
{
	t_function	*function;

	function = hashmap_get(functions, name);
	if (function == NULL)
		return (error(ERR_VAR_NOT_FOUND));
	function->active_count++;
	*out = function;
	return (error(ERR_NO));
}
