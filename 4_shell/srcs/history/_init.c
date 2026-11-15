/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:09:20 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/06 22:54:36 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"
#include "history_load_env.h"

void	history_init(t_history *history)
{
	*history = (t_history){0};
	history_list_init(&history->list);
	history_file_init(&history->file);
	history_adapter_init(&history->adapter);
	string_init(&history->current_input, 0, NULL, 0);
}

void	history_free(t_history *history)
{
	history_list_free(&history->list);
	history_file_free(&history->file);
	string_free(&history->current_input);
	history_adapter_free(&history->adapter);
}

t_error	history_load(t_history *history)
{
	ssize_t	max;

	if (load_history_path_from_env(history).type)
		return (history->err);
	if (load_history_max_size_env(history).type)
		return (history->err);
	max = history->adapter.max;
	history->err = history_file_load(&history->file, &history->list, max);
	if (history->err.type)
		return (history->err);
	history_adapter_load(&history->adapter, &history->list);
	return (history->err);
}
