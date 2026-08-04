/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 15:25:27 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 15:25:28 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>
#include "context_stack_item.h"

t_error	context_stack_item_init(
			t_context_stack_item **item,
			t_context context)
{
	*item = malloc(sizeof(t_context_stack_item));
	if (*item == NULL)
		return (error_sys());
	**item = (t_context_stack_item){0};
	(*item)->context = context;
	(*item)->end = SIZE_MAX;
	return (error(ERR_NO));
}

void	context_stack_item_free(void *item)
{
	free(*(t_context_stack_item **)item);
}
