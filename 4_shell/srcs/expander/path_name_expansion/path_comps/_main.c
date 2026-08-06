/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:45:12 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/05 23:09:30 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h> // DEBUG
#include "path_comps_.h"

bool	path_comps_have_special(const t_path_comps *comps)
{
	size_t		i;
	t_path_comp	*comp;

	i = 0;
	while (i < comps->len)
	{
		comp = &((t_path_comp *)comps->data)[i++];
		if (comp->special)
			return (true);
	}
	return (false);
}

void	path_comps_get(t_path_comp *out, const t_path_comps *src, size_t i)
{
	assert(src->len > 0 && i < src->len);
	*out = ((t_path_comp *)src->data)[i];
}
