/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_life_cycle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:09:29 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:09:30 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "options.h"

void	options_init(t_option *options)
{
	*options = 0u;
}

void	options_clear(t_option *options)
{
	*options = 0u;
}

void	options_free(t_option *options)
{
	(void)options;
	return ;
}
