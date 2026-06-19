/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 16:15:33 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/17 12:10:33 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "context.h"

t_error	context_stack_item_init(t_context_stack_item **item, t_context context)
{
	*item = malloc(sizeof(t_context_stack_item));
	if (*item == NULL)
		return (ERR_LIBC);
	**item = (t_context_stack_item){0};
	(*item)->context = context;
	return (ERR_NO);
}

void	context_stack_init(t_context_stack *stack)
{
	*stack = (t_context_stack){0};
	vector_init(stack, sizeof(t_context_stack_item *), 0);
}

void	context_stack_free(t_context_stack *stack)
{
	vector_free(stack, free);
	*stack = (t_context_stack){0};
}
