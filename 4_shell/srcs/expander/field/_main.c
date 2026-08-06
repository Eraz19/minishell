/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:43:30 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/06 22:52:23 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "field_.h"

t_error	fields_push(t_fields *fields, t_word item)
{
	if (!vector_push(fields, &item))
		return (error_sys());
	return (error(ERR_NO));
}

void	fields_fpop(t_word *out, t_fields *fields)
{
	vector_remove(fields, 0, out);
}
