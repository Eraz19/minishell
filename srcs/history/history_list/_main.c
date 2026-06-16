/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 15:20:42 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/16 13:16:41 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "__history_list.h"
#include "__history_file.h"

t_error	history_list_push(t_history_list *list, char *item)
{
	if (!vector_push(list, &item))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	history_list_insert(t_history_list *list, size_t index, char *item)
{
	if (!vector_insert(list, index, &item))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	history_list_get(char **item, size_t i, t_history_list *list)
{
	if (list->len == 0)
		return (error(ERR_EMPTY_STACK));
	else if (i >= list->len)
		return (error(ERR_INDEX_OUT_OF_BOUND));
	*item = ((char **)list->data)[i];
	return (error(ERR_NO));
}

t_error	history_list_to_file(t_history_list *list, size_t i, t_buff *content)
{
	t_error	err;
	char	*entry;

	while (i < list->len)
	{
		err = history_list_get(&entry, i, list);
		if (err)
			return (err);
		entry = str_dup(entry);
		if (entry == NULL)
			return (error_sys());
		err = history_file_entry_serialize(&entry);
		if (err)
			return (free(entry), err);
		if (!buff_append(content, entry, (long)str_len(entry)))
			return (free(entry), ERR_LIBC);
		free(entry);
		entry = NULL;
		i++;
	}
	return (free(entry), error(ERR_NO));
}
