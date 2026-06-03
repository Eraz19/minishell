/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 18:33:56 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/03 13:33:29 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "_history.h"

char	*history_find_last_unescaped_squote(char *entry)
{
	char	*match;
	char	saved;
	char	*result;

	if (entry == NULL)
		return (NULL);
	match = str_rchr(entry, '\'');
	if (match == NULL)
		return (NULL);
	if (match == entry || match[-1] != '\\')
		return (match);
	saved = match[-1];
	match[-1] = '\0';
	result = history_find_last_unescaped_squote(entry);
	match[-1] = saved;
	return (result);
}

void	history_remove_squote_escaping(char **entry)
{
	char	*match;
	char	*entry_;

	if (entry == NULL || *entry == NULL)
		return  ;
	entry_ = *entry;
	while (true)
	{
		match = str_chr(entry_, '\'');
		if (match == NULL)
			return ;
		else if (match > entry_ && match[-1] == '\\')
			ft_memmove(match - 1, match, str_len(match) + 1);
		entry_ = match + 1;
	}
}

static t_error	history_add_entry_escape_squote(t_buff *entry_, const char *src)
{
	ssize_t	match_i;

	if (!buff_append(entry_, src, (long)str_len(src)))
		return (ERR_LIBC);
	while (true)
	{
		match_i = buff_get_index(entry_, '\'');
		if (match_i == -1)
			return (ERR_NO);
		if (!buff_insert(entry_, (size_t)match_i, "\\", 1))
			return (ERR_LIBC);
	}
	return (ERR_NO);
}

t_error	history_add_squote_escaping(char **entry)
{
	t_buff	entry_;

	if (entry == NULL || *entry == NULL)
		return (ERR_NULL_ARGS);
	if (!buff_init(&entry_, 0, NULL, 0))
		return (buff_free(&entry_), ERR_LIBC);
	if (!buff_append(&entry_, "'", 1))
		return (buff_free(&entry_), ERR_LIBC);
	if (history_add_entry_escape_squote(&entry_, *entry))
		return (buff_free(&entry_), ERR_LIBC);
	if (!buff_append(&entry_, "'", 1))
		return (buff_free(&entry_), ERR_LIBC);
	free(*entry);
	*entry = buff_get_string(&entry_);
	if (*entry == NULL)
		return (buff_free(&entry_), ERR_LIBC);
	return (buff_free(&entry_), ERR_NO);
}
