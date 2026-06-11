/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 17:23:53 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/10 17:39:43 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input_stack_.h"

t_error	input_stack_pop(t_input_stack *stack)
{
	t_input_stack_item	*last_item;

	if (!vector_remove(stack, stack->len - 1, (void **)&last_item))
		return (ERR_LIBC);
	return (input_stack_clean(last_item), ERR_NO);
}

t_error	input_stack_push(t_input_stack *stack, t_input_stack_item item)
{
	if (!vector_push(stack, &item))
		return (ERR_LIBC);
	return (ERR_NO);
}

t_error	input_stack_get_last(t_input_stack *stack, t_input_stack_item *item)
{
	if (stack->len == 0)
		return (ERR_EMPTY_STACK);
	*item = ((t_input_stack_item *)stack->data)[stack->len - 1];
	return (ERR_NO);
}
