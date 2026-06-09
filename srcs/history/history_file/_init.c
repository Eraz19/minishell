/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 16:05:55 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/08 12:09:56 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "__history_file.h"

void	history_file_init(t_history_file *state)
{
	*state = (t_history_file){0};
	history_list_init(&state->loaded_list);
}

void	history_file_free(t_history_file *state)
{
	free(state->content);
	history_list_free(&state->loaded_list);
	*state = (t_history_file){0};
}

t_error	history_file_load(t_history_file *state, t_file_path path, ssize_t max)
{
	char 	*entry;

	state->path = path;
	if (history_file_read(state, &state->content))
		return (state->err);
	while ((max >= 0 && state->loaded_list.len < (size_t)max) || max < 0)
	{
		if (history_file_extract_prev_entry(state, &entry))
			return (state->err);
		if (entry == NULL)
			break ;
		history_file_entry_deserialize(&entry);
		state->err = history_list_insert(&state->loaded_list, 0, entry);
		if (state->err)
			return (free(entry), state->err);
		entry = NULL;
	}
	return (state->err);
}




