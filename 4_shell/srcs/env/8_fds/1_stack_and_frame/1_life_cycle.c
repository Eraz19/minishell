/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_life_cycle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:12:10 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:12:11 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect_stack.h"

/* ************************************************************************* */
/*                                   STACK                                   */
/* ************************************************************************* */

void	redirect_stack_init(t_redir_stack *stack)
{
	(void)vector_init(stack, sizeof(t_redir_frame), 0);
}

void	redirect_stack_clear(t_redir_stack *stack)
{
	vector_clear(stack, NULL);
}

void	redirect_stack_free(t_redir_stack *stack, size_t item_count_to_free)
{
	size_t	i;

	i = 0;
	while (i < item_count_to_free)
		redirect_frame_free(&((t_redir_frame *)stack->data)[i++]);
	vector_free(stack, NULL);
}

/* ************************************************************************* */
/*                                   FRAME                                   */
/* ************************************************************************* */

void	redirect_frame_init(t_redir_frame *frame)
{
	vector_init(frame, sizeof(t_redir_backup), 0);
}

void	redirect_frame_free(t_redir_frame *frame)
{
	vector_free(frame, NULL);
}
