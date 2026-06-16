/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 16:02:42 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/12 15:26:50 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "history_.h"
#include "history_file_.h"

t_error	history_file_open(t_history_file *state, int *fd, int flags)
{
	*fd = open(state->path, flags, 0644);
	if (*fd == -1 && errno != ENOENT)
		return (state->err = ERR_LIBC);
	if (*fd == -1)
	{
		*fd = open(state->path, O_CREAT | flags, 0644);
		if (*fd == -1)
			return (state->err = ERR_LIBC);
	}
	return (state->err);
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

t_error	history_file_extract(t_history_file *state, char **entry)
{
	char	*end;
	char	*start;

	*entry = NULL;
	if (state->content == NULL)
		return (state->err);
	end = history_file_entry_last_unescaped_squote(state->content);
	if (end == NULL)
		return (state->err);
	end[0] = '\0';
	start = history_file_entry_last_unescaped_squote(state->content);
	if (start == NULL)
		return (state->err = ERR_INCOHERENT_STATE);
	start[0] = '\0';
	*entry = str_sub(start, 1, (size_t)(end - start - 1));
	if (*entry == NULL)
		return (state->err = ERR_LIBC);
	return (history_entry_deserialize(entry), state->err);
}
