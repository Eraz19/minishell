/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:43:30 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/05 23:06:45 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h> // DEBUG
#include "field_.h"

t_error	fields_push(t_fields *fields, t_word item)
{
	if (!vector_push(fields, &item))
		return (error_sys());
	return (error(ERR_NO));
}

void	fields_fpop(t_word *out, t_fields *fields)
{
	assert(fields->len != 0);
	vector_remove(fields, 0, out);
}
