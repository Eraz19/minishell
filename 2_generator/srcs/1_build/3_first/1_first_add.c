/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_first_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:43:06 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/04 16:43:07 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator_first_priv.h"
#include "grammar_symbols.h"
#include <stdlib.h>

void	first_add(bool *dst, bool *did_add)
{
	if (did_add != NULL && *dst == false)
		*did_add = true;
	*dst = true;
}

void	first_add_list(bool *dst, const bool *src, bool *did_add)
{
	t_symbol	terminal;

	terminal = 0;
	while (terminal <= SYM_TERMINAL_MAX)
	{
		if (src[terminal] == true)
			first_add(&dst[terminal], did_add);
		terminal++;
	}
}
