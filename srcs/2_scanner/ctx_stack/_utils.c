/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 15:20:42 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/28 16:15:41 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_ctx_stack.h"

t_error	ctx_stack_push(t_scanner_ctx_stack *stack, t_scanner_ctx value)
{
	if (stack == NULL)
		return (ERR_NULL_ARGS);
	if (!vector_push(stack, &value))
		return (ERR_LIBC);
	return (ERR_NO);
}

t_error	ctx_stack_pop(t_scanner_ctx_stack *stack)
{
	if (stack == NULL)
		return (ERR_NULL_ARGS);
	if (!vector_pop(stack, NULL))
		return (ERR_EMPTY_STACK);
	return (ERR_NO);
}

t_error	ctx_stack_get(t_scanner_ctx *res, t_scanner_ctx_stack *stack)
{
	if (stack == NULL || res == NULL)
		return (ERR_NULL_ARGS);
	else if (stack->len == 0)
		return (ERR_EMPTY_STACK);
	*res = ((t_scanner_ctx *)stack->data)[stack->len - 1];
	return (ERR_NO);
}
