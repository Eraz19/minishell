/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_stack.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 15:25:20 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/06 22:43:02 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context_stack.h"
#include "context_stack_item.h"

t_error	context_stack_push(t_context_stack *stack, t_context_stack_item *item)
{
	if (!vector_push(stack, &item))
		return (error_sys());
	return (error(ERR_NO));
}

void	context_stack_bpop(t_context_stack *stack, t_context_stack_item **item)
{
	(void)vector_pop(stack, item);
}

void	context_stack_fpop(t_context_stack *stack, t_context_stack_item **item)
{
	(void)vector_remove(stack, 0, item);
}

void	context_stack_get(
			const t_context_stack *stack,
			t_context_stack_item **item,
			size_t index)
{
	*item = ((t_context_stack_item **)stack->data)[index];
}

t_error	context_stack_dup(t_context_stack *dst, const t_context_stack *src)
{
	size_t					i;
	t_error					err;
	t_context_stack_item	*src_item;
	t_context_stack_item	*dst_item;

	i = 0;
	context_stack_init(dst);
	while (i < src->len)
	{
		context_stack_get(src, &src_item, i++);
		err = context_stack_item_init(&dst_item, src_item->context);
		if (err.type)
			return (err);
		*dst_item = *src_item;
		dst_item->end = src_item->end;
		dst_item->start = src_item->start;
		err = context_stack_push(dst, dst_item);
		if (err.type)
			return (err);
	}
	return (error(ERR_NO));
}
