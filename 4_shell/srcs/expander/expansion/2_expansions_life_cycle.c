/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_expansions_life_cycle.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:42:59 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 17:43:00 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	cmd_expansions_init(t_expansions *expansions)
{
	(void)vector_init(expansions, sizeof(t_expansion), 0);
}

void	cmd_expansions_free(t_expansions *expansions)
{
	vector_free(expansions, expansion_free_void);
}
