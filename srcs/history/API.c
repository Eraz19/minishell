/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   API.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 16:34:10 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/16 16:51:43 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <stdlib.h>
#include "error.h"
#include "history.h"
#include "history_.h"

t_error	history_save_entry(void)
{
	char		*entry;
	t_history	*state;
	
	state = shell_get_history();
	if (state == NULL)
		return (ERR_SHELL_NOT_FOUND);
	if (state->current_input.len == 0)
		return (state->err);
	entry = buff_get_string(&state->current_input);
	if (entry == NULL)
		return (state->err = ERR_LIBC);
	state->err = history_list_push(&state->list, entry);
	if (state->err)
		return (free(entry), state->err);
	buff_free(&state->current_input);
	buff_init(&state->current_input, 0, NULL, 0);
	if (history_rl_add(&state->rl_history, &state->list, 1))
		return (state->err = state->rl_history.err);
	return (state->err);
}

t_error	history_append_to_entry(char *entry)
{
	t_history	*state;

	state = shell_get_history();
	if (state == NULL)
		return (error(ERR_SHELL_NOT_FOUND));
	if (!buff_append(&state->current_input, entry, (long)str_len(entry)))
		return (state->err = ERR_LIBC);
	return (state->err);
}

t_error	history_save(void)
{
	t_history	*state;

	state = shell_get_history();
	if (state == NULL)
		return (ERR_SHELL_NOT_FOUND);
	if (history_build_file_content(state, state->file.loaded_count))
		return (state->err);
	return (state->err = history_file_write(&state->file));
}
