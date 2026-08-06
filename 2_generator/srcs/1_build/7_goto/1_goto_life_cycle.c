/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_goto_life_cycle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:15:12 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 12:15:13 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator_goto.h"
#include <stdlib.h>

void	goto_init(size_t **gotos)
{
	*gotos = NULL;
}

void	goto_free(size_t **gotos)
{
	if (!gotos || !*gotos)
		return ;
	free(*gotos);
	*gotos = NULL;
}
