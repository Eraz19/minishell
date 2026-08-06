/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:43:23 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/06 22:52:19 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_.h"

t_error	expansion_push(t_expansion *expansion, t_string *str)
{
	if (!vector_push(expansion, str))
		return (error_sys());
	return (error(ERR_NO));
}

void	expansion_bpop(t_string *out, t_expansion *expansion)
{
	vector_pop(expansion, out);
}

void	expansion_fpop(t_string *out, t_expansion *expansion)
{
	vector_remove(expansion, 0, out);
}

void	expansion_get(t_string *out, const t_expansion *expansion, size_t i)
{
	*out = ((t_string *)expansion->data)[i];
}

void	expansion_take(t_expansion *exp, size_t i, t_string *out)
{
	vector_remove(exp, i, out);
}
