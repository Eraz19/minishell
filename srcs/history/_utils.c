/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 14:13:33 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/12 14:59:44 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "history.h"

void	history_entry_deserialize(char **entry)
{
	char	*match;
	char	*deserialized;

	deserialized = *entry;
	while (true)
	{
		match = str_chr(deserialized, '\'');
		if (match == NULL)
			return ;
		else if (match > deserialized && match[-1] == '\\')
			ft_memmove(match - 1, match, str_len(match) + 1);
		deserialized = match + 1;
	}
}

t_error	history_entry_serialize(char **entry)
{
	size_t	i;
	char	*entry_;
	t_buff	serialized;

	if (!buff_init(&serialized, 0, *entry, (long)str_len(*entry)))
		return (ERR_LIBC);
	i = 0;
	while (i < serialized.len)
	{
		if (serialized.data[i] == '\'')
		{
			if (!buff_insert(&serialized, (size_t)i++, "\\", 1))
				return (buff_free(&serialized), ERR_LIBC);
		}
		i++;
	}
	if (!buff_prepend(&serialized, "'", 1))
		return (buff_free(&serialized), ERR_LIBC);
	if (!buff_append(&serialized, "'", 1))
		return (buff_free(&serialized), ERR_LIBC);
	entry_ = buff_get_string(&serialized);
	if (entry_ == NULL)
		return (buff_free(&serialized), ERR_LIBC);
	return (free(*entry), *entry = entry_, buff_free(&serialized), ERR_NO);
}

t_error	history_build_file_content(t_history *state, size_t start)
{
	size_t	i;
	char	*entry;
	t_buff	content;

	i = start;
	free(state->file.content);
	buff_init(&content, 0, NULL, 0);
	while (i < state->list.len)
	{
		state->err = history_list_get(&state->list, &entry, i);
		if (state->err)
			return (state->err);
		if (!buff_append(&content, entry, (long)str_len(entry)))
			return (free(entry), buff_free(&content), state->err = ERR_LIBC);
		free(entry);
		entry = NULL;
		i++;
	}
	state->file.content = buff_get_string(&content);
	if (state->file.content == NULL)
		return (buff_free(&content), state->err = ERR_LIBC);
	return (buff_free(&content), state->err);
}
