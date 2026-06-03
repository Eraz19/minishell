/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 13:19:38 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/03 13:53:44 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "error.h"
#include "_history.h"

void	history_init(t_history *state)
{
	if (state == NULL)
		return ;
	*state = (t_history){0};
	history_list_init(&state->entries);
	buff_init(&state->current_input, 0, NULL, 0);
}

void	history_free(t_history *state)
{
	history_list_free(&state->entries);
	buff_free(&state->current_input);
	history_rl_history_free(state);
	*state = (t_history){0};
}

static t_error	history_clean_entry(char **entry, char *start, char *end)
{
	*entry = str_sub(start + 1, 0, (size_t)(end - start - 1));
	if (*entry == NULL)
		return (ERR_LIBC);
	return (history_remove_squote_escaping(entry), ERR_NO);
}

static t_error	history_load_entries(char *content, t_history *state)
{
	char	*end;
	char	*start;
	char 	*entry;

	end = NULL;
	start = NULL;
	while (state->entries.len < (size_t)state->max_entries)
	{
		end = history_find_last_unescaped_squote(content);
		if (end == NULL)
			break ;
		*end = '\0';
		start = history_find_last_unescaped_squote(content);
		if (start == NULL)
			return (state->err = ERR_INCOHERENT_STATE, state->err);
		*start = '\0';
		state->err = history_clean_entry(&entry, start, end);
		if (state->err)
			return (state->err);
		state->err = history_list_insert(&state->entries, 0, entry);
		if (state->err)
			return (free(entry), state->err);
		entry = NULL;
	}
	return (state->loaded_entries = state->entries.len, state->err);
}

t_error	history_load(t_history *state, const char *path, ssize_t max_entries)
{
	char	*content;

	if (state == NULL || path == NULL)
		return (ERR_NULL_ARGS);
	state->path = path;
	if (max_entries >= 0 && max_entries < 128)
		state->max_entries = 128;
	else
		state->max_entries = max_entries;
	if (history_read_file(&content, state))
		return (state->err);
	if (history_load_entries(content, state))
		return (free(content), state->err);
	history_rl_add_entries(state, state->loaded_entries);
	return (free(content), state->err);
}
