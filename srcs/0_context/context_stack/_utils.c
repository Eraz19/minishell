/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 15:20:42 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/16 13:02:05 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"

t_error	context_stack_push(t_context_stack *stack, t_context item)
{
	if (!vector_push(stack, &item))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	context_stack_pop(t_context_stack *stack)
{
	if (!vector_pop(stack, NULL))
		return (error(ERR_EMPTY_STACK));
	return (error(ERR_NO));
}

t_error	context_stack_get(t_context_stack *stack, t_context *item)
{
	if (stack->len == 0)
		return (error(ERR_EMPTY_STACK));
	return (*item = ((t_context *)stack->data)[stack->len - 1], error(ERR_NO));
}
