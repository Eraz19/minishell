/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 10:40:13 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/12 16:10:08 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alias_.h"
#include "context.h"

void	set_position_for_next_word(t_alias *state, char *expansion)
{
	size_t	expansion_len;
	
	if (expansion == NULL)
		return ;
	expansion_len = str_len(expansion);
	if (expansion != NULL && is_blank(expansion[expansion_len - 1]))
		state->disable_position = true;
	else
		state->disable_position = false;
}
