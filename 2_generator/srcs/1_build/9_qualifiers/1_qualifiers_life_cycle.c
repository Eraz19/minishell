/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_qualifiers_life_cycle.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:16:26 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 12:16:27 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator_qualifiers.h"
#include <stdlib.h>

void	qualifiers_init(t_qualifier **qualifiers)
{
	*qualifiers = NULL;
}

void	qualifiers_free(t_qualifier **qualifiers)
{
	if (!qualifiers || !*qualifiers)
		return ;
	free(*qualifiers);
	*qualifiers = NULL;
}
