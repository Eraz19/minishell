/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 13:19:38 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/09 17:25:56 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "error.h"
#include "params.h"
#include "history.h"
#include "__history_rl.h"

void	history_init(t_history *state)
{
	*state = (t_history){0};
	history_list_init(&state->list);
	history_file_init(&state->file);
	history_rl_init(&state->rl_history);
	buff_init(&state->current_input, 0, NULL, 0);
}

void	history_free(t_history *state)
{
	history_list_free(&state->list);
	history_file_free(&state->file);
	buff_free(&state->current_input);
	history_rl_free(&state->rl_history);
	*state = (t_history){0};
}

t_error	history_load(t_history *state)
{
	t_file_path	path;
	char		*max_as_string;
	ssize_t 	max;
	ssize_t		max_entries;
	t_error		error;

	/* -------- TODO (START) -------- */
	error = params_get("HISTFILE", &path);
	if (error != ERR_NO && error != ERR_VAR_NOT_FOUND)
		return (error);
	if (error == ERR_VAR_NOT_FOUND || path == NULL)
	{
		// TODO: create history file in $HOME/.sh_history
	}
	error = params_get("HISTSIZE", &max_as_string);
	if (error != ERR_NO && error != ERR_VAR_NOT_FOUND)
		return (error);
	if (error == ERR_VAR_NOT_FOUND || max_as_string == NULL)
	{
		// TODO: ???
	}
	/* -------- TODO (END) -------- */
	max = (ssize_t)ft_atol(max_as_string);
	max_entries = max;
	if (max >= 0 && max < 128)
		max_entries = 128;
	if (history_file_load(&state->file, path, max_entries))
		return (state->err = state->file.err, state->err);
	if (!vector_dup(&state->list, &state->file.loaded_list))
		return (state->err = ERR_LIBC, state->err);
	history_rl_load(&state->rl_history, max_entries);
	if (history_rl_add(&state->rl_history, &state->list, state->list.len))
		return (state->err = state->rl_history.err, state->err);
	return (state->err);
}
