/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:45:12 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/06 22:52:29 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	*out = ((t_path_comp *)src->data)[i];
}
