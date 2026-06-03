/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 08:36:50 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/03 14:00:14 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <readline/readline.h>
#include "_history.h"

static ssize_t	get_entries_to_add_count(t_history *state, size_t count)
{
	if (state->max_entries < 0)
		return ((ssize_t)count);
	else if (state->entries_in_rlhistory + count > (size_t)(state->max_entries))
		return (-(ssize_t)state->max_entries);
	else
		return ((ssize_t)count);
}

static t_error	add_history_(t_history_list *entries, size_t *i)
{
	t_error	err;
	char	*entry;

	err = history_list_get(&entry, (size_t)(*i)++, entries);
	if (err)
		return (err);
	return (add_history(entry), ERR_NO);
}

t_error	history_rl_add_entries(t_history *state, size_t count)
{
	ssize_t	i;
	ssize_t	entries_to_add;

	if (state == NULL)
		return (ERR_NULL_ARGS);
	if (count == 0)
		return (state->err);
	entries_to_add = get_entries_to_add_count(state, count);
	if (entries_to_add < 0)
	{
		history_rl_history_free(state);
		entries_to_add = -entries_to_add;
	}
	i = (ssize_t)state->entries.len - entries_to_add;
	if (i < 0)
		i = 0;
	while (i < (ssize_t)state->entries.len)
	{
		state->err = add_history_(&state->entries, (size_t *)&i);
		if (state->err)
			return (state->err);
		state->entries_in_rlhistory++;
	}
	return (state->err);
}

void	history_rl_history_free(t_history *state)
{
	rl_clear_history();
	state->entries_in_rlhistory = 0;
}
