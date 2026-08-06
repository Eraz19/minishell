/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_adapter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:08:18 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/06 22:54:40 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/history.h>
#include "history_adapter.h"

void	add_to_readline_history(
			t_history_adapter *history_adapter,
			t_history_list *history_list,
			size_t count)
{
	size_t			i;
	const t_string	*entry;
	ssize_t			max_size;

	if (count == 0)
		return ;
	max_size = history_adapter->max;
	if (max_size >= 0 && history_adapter->count + count > (size_t)max_size)
	{
		history_adapter_free(history_adapter);
		if ((size_t)history_adapter->max >= history_list->len)
			i = 0;
		else
			i = history_list->len - (size_t)history_adapter->max;
	}
	else
		i = history_list->len - count;
	while (i < history_list->len)
	{
		history_list_get(history_list, &entry, i++);
		add_history(entry->data);
		history_adapter->count++;
	}
	success_history_adapter_add_log(history_adapter);
}
