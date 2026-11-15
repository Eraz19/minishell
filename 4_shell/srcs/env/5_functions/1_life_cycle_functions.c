/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_life_cycle_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:11:31 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 15:08:27 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.h"
#include "functions_priv.h"
#include <stdlib.h>

static void	function_free_void(void *function)
{
	t_function	*func;

	func = (t_function *)function;
	function_free(&func);
}

void	functions_init(t_functions *functions)
{
	hashmap_init(functions, 0, NULL);
}

void	functions_clear(t_functions *functions)
{
	hashmap_clear(functions);
}

void	functions_free(t_functions *functions)
{
	functions->del_value = function_free_void;
	hashmap_free(functions);
}
