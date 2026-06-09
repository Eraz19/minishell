/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 16:15:33 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/09 16:01:42 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"

void	context_stack_init(t_context_stack *stack)
{
	*stack = (t_context_stack){0};
	vector_init(stack, sizeof(t_context), 0);
}

void	context_stack_free(t_context_stack *stack)
{
	vector_free(stack, NULL);
	*stack = (t_context_stack){0};
}
