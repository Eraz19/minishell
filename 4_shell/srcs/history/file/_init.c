/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:08:26 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/05 19:02:29 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "utils.h"
#include "history_list.h"
#include "history_file.h"
#include "history_file_priv.h"

void	history_file_init(t_history_file *history_file)
{
	*history_file = (t_history_file){0};
	(void)string_init(&history_file->path, 0, NULL, 0);
	(void)string_init(&history_file->content, 0, NULL, 0);
}

void	history_file_free(t_history_file *history_file)
{
	history_file->loaded_count = 0;
	string_free(&history_file->path);
	string_free(&history_file->content);
}

t_error	history_file_load(
			t_history_file *history_file,
			t_history_list *history_list,
			ssize_t max)
{
	size_t		index;
	t_vector	file_entries;

	if (read_history_file(history_file).type)
		return (history_file->err);
	if (history_file->content.len == 0)
		return (empty_history_file_load_log(), history_file->err);
	history_file->err = deserialize_all(
			history_file->content.data,
			&file_entries);
	if (history_file->err.type)
		return (history_file->err);
	if (max < 0 || (size_t)max >= file_entries.len)
		index = 0;
	else
		index = file_entries.len - (size_t)max;
	history_file->err = history_list_load(history_list, &file_entries, index);
	if (history_file->err.type)
		return (vector_free(&file_entries, string_free_void),
			history_file->err);
	history_file->loaded_count = history_list->len;
	vector_free(&file_entries, string_free_void);
	string_free(&history_file->content);
	success_history_file_load_log(history_file);
	return (history_file->err);
}
