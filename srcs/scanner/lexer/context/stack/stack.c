/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 16:05:22 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/19 18:02:35 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "_stack.h"

void	free_ctx_stack(t_ctx_stack *stack)
{
	free(stack->data);
	stack->len = 0;
	stack->size = 0;
	stack->data = NULL;
}

t_error	ctx_update_nesting(t_ctx_stack *stack, int value)
{
	if (stack->data[stack->len - 1].nesting_depth + value < 0)
		return (ERR_VALUE_OUT_OF_RANGE);
	return (stack->data[stack->len - 1].nesting_depth += value, ERR_NO);
}

t_error	ctx_push(t_ctx_stack *stack, t_lexer_ctx_type ctx)
{
	t_lexer_ctx	*tmp;

	if (stack == NULL)
		return (ERR_NULL_ARGS);
	tmp = NULL;
	if (stack->size == 0)
	{
		stack->data = malloc(sizeof(t_lexer_ctx) * 1);
		if (stack->data == NULL)
			return (ERR_LIBC);
		stack->size = 1;
	}
	else if (stack->len + 1 > stack->size)
	{
		tmp = malloc(sizeof(t_lexer_ctx) * (stack->size * 2));
		if (tmp == NULL)
			return (ERR_LIBC);
		tmp = ft_memcpy(tmp, stack->data, stack->len * sizeof(t_lexer_ctx));
		free(stack->data);
		stack->data = tmp;
		stack->size *= 2;
	}
	stack->data[stack->len++] = (t_lexer_ctx){.type = ctx, .nesting_depth = 0};
	return (ERR_NO);
}

t_lexer_ctx	ctx_pop(t_ctx_stack *stack)
{
	if (stack == NULL || stack->len == 0)
		return ((t_lexer_ctx){.type = NONE, .nesting_depth = 0});
	return (stack->data[--stack->len]);
}

t_lexer_ctx	ctx_view(t_ctx_stack *stack)
{
	if (stack == NULL || stack->len == 0)
		return ((t_lexer_ctx){.type = NONE, .nesting_depth = 0});
	return (stack->data[stack->len - 1]);
}
