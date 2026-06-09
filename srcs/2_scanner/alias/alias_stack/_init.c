/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 16:15:33 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/09 16:13:49 by gastesan         ###   ########.fr       */
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
	vector_free(stack, NULL);
	*stack = (t_alias_stack){0};
}
