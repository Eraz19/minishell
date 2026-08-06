/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_function_stop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:11:39 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:11:40 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions_priv.h"
#include <assert.h>

void	function_stop(t_function **function)
{
	assert((*function)->active_count > 0);
	(*function)->active_count--;
	if ((*function)->active_count == 0 && (*function)->pending_free == true)
		function_free(function);
}
