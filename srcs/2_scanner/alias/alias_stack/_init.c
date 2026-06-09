/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 16:15:33 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/08 14:37:14 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "__alias_stack.h"

void	alias_stack_init(t_alias_stack *stack)
{
	*stack = (t_alias_stack){0};
	vector_init(stack, sizeof(char *), 0);
}

void	alias_stack_free(t_alias_stack *stack)
{
	vector_free(stack);
	*stack = (t_alias_stack){0};
}
