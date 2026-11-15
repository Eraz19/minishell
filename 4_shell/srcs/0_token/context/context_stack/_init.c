/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 15:25:16 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 15:25:17 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context_stack.h"
#include "context_stack_item.h"

void	context_stack_init(t_context_stack *stack)
{
	*stack = (t_context_stack){0};
	vector_init(stack, sizeof(t_context_stack_item *), 0);
}

void	context_stack_free(t_context_stack *stack)
{
	vector_free(stack, context_stack_item_free);
}
