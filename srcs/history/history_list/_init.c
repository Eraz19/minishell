/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 16:15:33 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/02 17:05:17 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "_history_list.h"

void	history_list_init(t_history_list *list)
{
	if (list == NULL)
		return ;
	*list = (t_history_list){0};
	vector_init(list, sizeof(char *), 0);
}

void	history_list_free(t_history_list *list)
{
	size_t	i;

	i = 0;
	if (list == NULL)
		return ;
	while (i < list->len)
	{
		free(((char **)list->data)[i]);
		((char **)list->data)[i++] = NULL;
	}
	vector_free(list);
	*list = (t_history_list){0};
}
