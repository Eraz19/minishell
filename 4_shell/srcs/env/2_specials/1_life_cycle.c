/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_life_cycle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:09:51 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:09:52 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "specials.h"
#include <stdlib.h>

void	specials_init(t_specials *specials)
{
	string_init(&specials->zero, 0, NULL, 0);
	string_init(&specials->source, 0, NULL, 0);
	specials->pid = -1;
	specials->last_bg_pid = -1;
	specials->last_status = 0;
}

void	specials_clear(t_specials *specials)
{
	specials_init(specials);
}

void	specials_free(t_specials *specials)
{
	specials_init(specials);
}
