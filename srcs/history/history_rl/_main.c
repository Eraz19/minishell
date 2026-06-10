/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 08:36:50 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/10 16:33:51 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/history.h>
#include "history_rl_.h"
#include "history_list_.h"

t_error	history_rl_add(t_history_rl *state, t_history_list *list, size_t count)
{
	ssize_t	i;
	char	*entry;
	ssize_t	entries_to_add;

	if (count == 0)
		return (state->err);
	entries_to_add = history_rl_to_add_count(state, count);
	if (entries_to_add < 0)
	{
		history_rl_free(state);
		entries_to_add = -entries_to_add;
	}
	i = (ssize_t)list->len - entries_to_add;
	if (i < 0)
		i = 0;
	while ((size_t)i < list->len)
	{
		state->err = history_list_get(&entry, (size_t)i++, list);
		if (state->err)
			return (state->err);
		add_history(entry);
		state->count++;
	}
	return (state->err);
}
