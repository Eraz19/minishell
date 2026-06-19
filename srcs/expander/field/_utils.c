/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 10:32:57 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/18 13:35:37 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_field_.h"

t_error	expander_fields_push(t_expander_fields *fields, t_expander_word item)
{
	if (!vector_push(fields, &item))
		return (ERR_LIBC);
	return (ERR_NO);
}

t_error	expander_fields_pop(t_expander_fields *fields, t_expander_word *item)
{
	if (fields->len == 0)
		return (ERR_EMPTY_STACK);
	if (!vector_remove(fields, 0, item))
		return (ERR_LIBC);
	return (ERR_NO);
}
