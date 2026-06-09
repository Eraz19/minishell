/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   API.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 13:20:55 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/08 11:27:46 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "error.h"
#include "__history.h"

t_error	history_save_entry(void)
{
	char		*entry;
	t_history	*state;
	
	state = shell_get_history();
	entry = buff_get_string(&state->current_input);
	if (entry == NULL)
		return (state->err = ERR_LIBC, state->err);
	state->err = history_list_push(&state->list, entry);
	if (state->err)
		return (free(entry), state->err);
	buff_free(&state->current_input);
	buff_init(&state->current_input, 0, NULL, 0);
	if (history_rl_add(&state->rl_history, &state->list, 1))
		return (state->err = state->rl_history.err, state->err);
	return (state->err);
}

t_error	history_append_to_entry(char *entry)
{
	t_history	*state;

	state = shell_get_history();
	if (!buff_append(&state->current_input, entry, (long)str_len(entry)))
		return (state->err = ERR_LIBC, state->err);
	return (state->err);
}

t_error	history_save(void)
{
	size_t		i;
	t_history	*state;
	t_buff		content;
	char 		*content_str;

	state = shell_get_history();
	buff_init(&content, 0, NULL, 0);
	i = state->file.loaded_list.len;
	state->err = history_list_to_file(&state->list, i, &content);
	if (state->err)
		return (buff_free(&content), state->err);
	content_str = buff_get_string(&content);
	if (content_str == NULL)
		return (buff_free(&content), state->err = ERR_LIBC, state->err);
	if (history_file_write(&state->file, content_str))
		state->err = state->file.err;	
	return (buff_free(&content), free(content_str), state->err);
}
