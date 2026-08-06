/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:43:23 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/05 23:28:59 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h> // DEBUG
#include "expansion_.h"

t_error	expansion_push(t_expansion *expansion, t_string *str)
{
	if (!vector_push(expansion, str))
		return (error_sys());
	return (error(ERR_NO));
}

void	expansion_bpop(t_string *out, t_expansion *expansion)
{
	assert(expansion->len != 0);
	vector_pop(expansion, out);
}

void	expansion_fpop(t_string *out, t_expansion *expansion)
{
	assert(expansion->len != 0);
	vector_remove(expansion, 0, out);
}

void	expansion_get(t_string *out, const t_expansion *expansion, size_t i)
{
	assert(expansion->len > 0 && i < expansion->len);
	*out = ((t_string *)expansion->data)[i];
}

void	expansion_take(t_expansion *exp, size_t i, t_string *out)
{
	assert(i < exp->len);
	vector_remove(exp, i, out);
}
