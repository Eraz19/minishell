/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 13:19:38 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/20 11:24:30 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "error.h"
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

# include "logs.h"	// DEBUG
t_error	history_load(t_history *state)
{
	ssize_t	max;

	print_title("history_load()");
	if (history_load_path_env(state).type)
		return (state->err);
	print_pass("history_load_path_env()\n");
	max = state->rl_history.max;
	if (history_load_size_env(state).type)
		return (state->err);
	print_pass("history_load_size_env()\n");
	if (history_file_load(&state->file, &state->list, max).type)
		return (state->err = state->file.err);
	print_pass("history_file_load()\n");
	if (history_rl_load(&state->rl_history, &state->list).type)
		return (state->err = state->rl_history.err);
	print_pass("history_rl_load()\n");
	print_result("history_load()");
	return (state->err);
}
