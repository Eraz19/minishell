/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 16:02:42 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/08 12:35:33 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "types.h"
#include "__history_file.h"

t_error	history_file_open(t_history_file *state, int *fd, int flags)
{
	*fd = open(state->path, flags, 0644);
	if (*fd == -1 && errno != ENOENT)
		return (state->err = ERR_LIBC, state->err);
	if (*fd == -1)
	{
		*fd = open(state->path, O_CREAT | flags, 0644);
		if (*fd == -1)
			return (state->err = ERR_LIBC, state->err);
	}
	return (state->err);
}

void	history_file_entry_deserialize(char **entry)
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

t_error	history_file_entry_serialize(char **entry)
{
	size_t	i;
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
	free(*entry);
	*entry = buff_get_string(&serialized);
	if (*entry == NULL)
		return (buff_free(&serialized), ERR_LIBC);
	return (buff_free(&serialized), ERR_NO);
}

static char	*history_file_entry_last_unescaped_squote(char *entry)
{
	char	*match;
	char	*result;

	match = str_rchr(entry, '\'');
	if (match == NULL)
		return (NULL);
	if (match == entry || match[-1] != '\\')
		return (match);
	match[-1] = '\0';
	result = history_file_entry_last_unescaped_squote(entry);
	match[-1] = '\\';
	return (result);
}

t_error	history_file_extract_prev_entry(t_history_file *state, char **entry)
{
	char	*end;
	char	*start;
	
	end = history_file_entry_last_unescaped_squote(state->content);
	if (end == NULL)
		return (state->err);
	end[0] = '\0';
	start = history_file_entry_last_unescaped_squote(state->content);
	if (start == NULL)
		return (state->err = ERR_INCOHERENT_STATE, state->err);
	start[0] = '\0';
	*entry = str_sub(start, 1, (size_t)(end - start - 1));
	if (*entry == NULL)
		return (state->err = ERR_LIBC, state->err);
	return (state->err);
}
