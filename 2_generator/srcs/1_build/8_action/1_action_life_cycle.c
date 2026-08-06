/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_action_life_cycle.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:15:26 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 12:15:27 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator_actions.h"
#include <stdlib.h>

void	action_init(t_action **actions)
{
	*actions = NULL;
}

void	action_free(t_action **actions)
{
	if (!actions || !*actions)
		return ;
	free(*actions);
	*actions = NULL;
}
