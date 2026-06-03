/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 15:20:42 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/03 13:18:36 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "time.h"
#include "_history_list.h"

t_error	history_list_push(t_history_list *list, char *item)
{
	if (list == NULL || item == NULL)
		return (ERR_NULL_ARGS);
	if (!vector_push(list, &item))
		return (ERR_LIBC);
	return (ERR_NO);
}

t_error	history_list_insert(t_history_list *list, size_t index, char *item)
{
	if (list == NULL || item == NULL)
		return (ERR_NULL_ARGS);
	if (!vector_insert(list, index, &item))
		return (ERR_LIBC);
	return (ERR_NO);
}

t_error	history_list_get(char **item, size_t i, t_history_list *list)
{
	if (list == NULL || item == NULL)
		return (ERR_NULL_ARGS);
	else if (list->len == 0)
		return (ERR_EMPTY_STACK);
	else if (i >= list->len)
		return (ERR_INDEX_OUT_OF_BOUND);
	*item = ((char **)list->data)[i];
	return (ERR_NO);
}
