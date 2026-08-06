/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:08:50 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/05 17:12:21 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history_list.h"

void	history_list_init(t_history_list *list)
{
	vector_init(list, sizeof(t_string), 0);
}

void	history_list_free(t_history_list *list)
{
	vector_free(list, string_free_void);
}

t_error	history_list_load(
			t_history_list *history_list,
			t_vector *entries,
			size_t start)
{
	size_t		i;
	t_error		err;
	t_string	owned;
	t_string	*entry;

	i = start;
	err = error(ERR_NO);
	while (i < entries->len)
	{
		entry = &((t_string *)entries->data)[i++];
		string_take_string(&owned, entry);
		err = history_list_push(history_list, &owned);
		if (err.type)
			return (err);
	}
	return (err);
}
