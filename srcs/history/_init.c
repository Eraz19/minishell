/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 13:19:38 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/10 16:32:26 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "error.h"
#include "params.h"
#include "history_.h"

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
	if (history_load_path_env(state) != ERR_NO)
		return (state->err);
	if (history_load_size_env(state) != ERR_NO)
		return (state->err);
	if (history_file_load(&state->file, state->rl_history.max))
		return (state->err = state->file.err, state->err);
	if (!vector_dup(&state->list, &state->file.loaded_list))
		return (state->err = ERR_LIBC, state->err);
	if (history_rl_load(&state->rl_history, &state->list))
		return (state->err = state->rl_history.err, state->err);
	return (state->err);
}
