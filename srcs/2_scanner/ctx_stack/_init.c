/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 16:15:33 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/29 15:21:34 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_ctx_stack.h"

void	ctx_stack_init(t_scanner_ctx_stack *stack)
{
	if (stack == NULL)
		return ;
	*stack = (t_scanner_ctx_stack){0};
	vector_init(stack, sizeof(t_scanner_ctx), 0);
}

void	ctx_stack_free(t_scanner_ctx_stack *stack)
{
	if (stack == NULL)
		return ;
	vector_free(stack);
	*stack = (t_scanner_ctx_stack){0};
}
