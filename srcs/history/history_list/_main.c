/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 15:20:42 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/12 14:37:39 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "history_.h"
#include "history_list_.h"
#include "history_file_.h"

t_error	history_list_push(t_history_list *list, char *item)
{
	if (!vector_push(list, &item))
		return (ERR_LIBC);
	return (ERR_NO);
}

t_error	history_list_insert(t_history_list *list, char *item, size_t index)
{
	if (!vector_insert(list, index, &item))
		return (ERR_LIBC);
	return (ERR_NO);
}

t_error	history_list_get(t_history_list *list, char **item, size_t i)
{
	t_error	err;
	char	*item_;

	if (list->len == 0)
		return (ERR_EMPTY_STACK);
	else if (i >= list->len)
		return (ERR_INDEX_OUT_OF_BOUND);
	item_ = str_dup(((char **)list->data)[i]);
	if (item_ == NULL)
		return (ERR_LIBC);
	err = history_entry_serialize(&item_);
	if (err)
		return (free(item_), err);
	return (*item = item_, ERR_NO);
}
