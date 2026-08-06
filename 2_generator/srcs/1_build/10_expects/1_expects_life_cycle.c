/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_expects_life_cycle.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:18:38 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 12:18:39 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator_expects.h"
#include <stdlib.h>

void	expects_init(bool **expects)
{
	*expects = NULL;
}

void	expects_free(bool **expects)
{
	if (!expects || !*expects)
		return ;
	free(*expects);
	*expects = NULL;
}
