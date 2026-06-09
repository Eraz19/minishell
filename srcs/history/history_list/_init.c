/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 16:15:33 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/08 11:06:35 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "__history_list.h"

void	history_list_init(t_history_list *list)
{
	*list = (t_history_list){0};
	vector_init(list, sizeof(char *), 0);
}

void	history_list_free(t_history_list *list)
{
	size_t	i;

	i = 0;
	while (i < list->len)
	{
		if (((char **)list->data)[i] != NULL)
		{
			free(((char **)list->data)[i]);
			((char **)list->data)[i++] = NULL;
		}
	}
	vector_free(list);
	*list = (t_history_list){0};
}
