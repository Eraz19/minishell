/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   API.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 13:20:55 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/03 13:27:17 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "error.h"
#include "_history.h"

t_error	history_save_entry(void)
{
	char		*entry;
	t_history	*state;
	
	state = shell_get_history();
	if (state == NULL)
		return (ERR_NULL_ARGS);
	entry = buff_get_string(&state->current_input);
	if (entry == NULL)
		return (state->err = ERR_LIBC, state->err);
	state->err = history_list_push(&state->entries, entry);
	if (state->err)
		return (free(entry), state->err);
	buff_free(&state->current_input);
	buff_init(&state->current_input, 0, NULL, 0);
	return (history_rl_add_entries(state, 1), state->err);
}

t_error	history_append_to_entry(char *entry)
{
	t_history	*state;

	state = shell_get_history();
	if (state == NULL || entry == NULL)
		return (ERR_NULL_ARGS);
	if (!buff_append(&state->current_input, entry, (long)str_len(entry)))
		return (state->err = ERR_LIBC, state->err);
	return (state->err);
}

static t_error	content_append(t_history *state, size_t i, t_buff *content)
{
	char	*entry;

	state->err = history_list_get(&entry, i, &state->entries);
	if (state->err)
		return (state->err);
	entry = str_dup(entry);
	if (entry == NULL)
		return (state->err = ERR_LIBC, state->err);
	state->err = history_add_squote_escaping(&entry);
	if (state->err)
		return (free(entry), state->err);
	if (!buff_append(content, entry, (long)str_len(entry)))
		return (free(entry), state->err = ERR_LIBC, state->err);
	return (free(entry), state->err);
}

t_error	history_save_in_file(void)
{
	size_t		i;
	t_history	*state;
	t_buff		content;
	char 		*content_str;

	state = shell_get_history();
	if (state == NULL)
		return (ERR_NULL_ARGS);
	else if (state->path == NULL)
		return (state->err = ERR_INCOHERENT_STATE, state->err);
	if (!buff_init(&content, 0, NULL, 0))
		return (state->err = ERR_LIBC, state->err);
	i = state->loaded_entries;
	while (i < state->entries.len)
	{
		content_append(state, i, &content);
		if (state->err)
			return (buff_free(&content), state->err);
		i++;
	}
	content_str = buff_get_string(&content);
	if (content_str == NULL)
		return (buff_free(&content), state->err = ERR_LIBC, state->err);
	history_write_in_file(state, content_str);
	return (buff_free(&content), free(content_str), state->err);
}
