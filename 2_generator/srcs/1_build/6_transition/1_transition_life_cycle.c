/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_transition_life_cycle.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:14:24 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 12:14:25 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator_transitions.h"

void	transition_init(t_vector *transitions)
{
	vector_init(transitions, sizeof(t_transition), 0);
}

void	transition_free(t_vector *transitions)
{
	vector_free(transitions, NULL);
}
