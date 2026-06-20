/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 15:20:42 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/19 15:58:39 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"

t_error	context_stack_push(t_context_stack *stack, t_context_stack_item *item)
{
	if (!vector_push(stack, &item))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	context_stack_bpop(t_context_stack *stack, t_context_stack_item **item)
{
	if (stack->len == 0)
		return (error(ERR_EMPTY_STACK));
	if (!vector_pop(stack, item))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	context_stack_fpop(t_context_stack *stack, t_context_stack_item **item)
{
	if (stack->len == 0)
		return (error(ERR_EMPTY_STACK));
	if (!vector_remove(stack, 0, item))
		return (error_sys());
	return (error(ERR_NO));
}

t_error	context_stack_get(
	t_context_stack *stack,
	t_context_stack_item **item,
	size_t index)
{
	if (stack->len == 0)
		return (error(ERR_EMPTY_STACK));
	if (index >= stack->len)
		return (error(ERR_INDEX_OUT_OF_BOUND));
	*item = ((t_context_stack_item **)stack->data)[index];
	return (error(ERR_NO));
}

t_error	context_stack_dup(t_context_stack *dst, t_context_stack *src)
{
	size_t					i;
	t_error					err;
	t_context_stack_item	*src_item;
	t_context_stack_item	*dst_item;

	i = 0;
	while (i < src->len)
	{
		err = context_stack_get(src, &src_item, i);
		if (err.type)
			return (err);
		err = context_stack_item_init(&dst_item, src_item->context);
		if (err.type)
			return (err);
		*dst_item = *src_item;
		dst_item->end = src_item->end;
		dst_item->start = src_item->start;
		err = context_stack_push(dst, dst_item);
		if (err.type)
			return (err);
		i++;
	}
	return (error(ERR_NO));
}
