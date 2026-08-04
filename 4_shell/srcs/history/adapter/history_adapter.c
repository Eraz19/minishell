/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_adapter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:08:18 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 17:23:50 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/history.h>
#include "history_adapter_priv.h"

void	add_to_readline_history(
			t_history_adapter *history_adapter,
			t_history_list *history_list,
			size_t count)
{
	size_t			i;
	const t_string	*entry;

	if (count == 0)
		return ;
	if (history_adapter->max < 0
		|| (size_t)history_adapter->max >= history_list->len)
		i = 0;
	else
		i = history_list->len - (size_t)history_adapter->max;
	history_adapter_free(history_adapter);
	while (i < history_list->len)
	{
		history_list_get(history_list, &entry, (size_t)i++);
		add_history(entry->data);
		history_adapter->count++;
	}
	success_history_adapter_add_log(history_adapter);
}
