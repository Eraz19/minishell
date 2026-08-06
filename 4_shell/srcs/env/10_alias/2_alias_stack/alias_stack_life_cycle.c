/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_stack_life_cycle.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:14:28 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:14:29 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alias_stack_internal.h"

void	alias_stack_init(t_alias_stack *stack)
{
	(void)vector_init(stack, sizeof(t_string), 0);
}

void	alias_stack_clear(t_alias_stack *stack)
{
	vector_clear(stack, string_free_void);
}

void	alias_stack_free(t_alias_stack *stack)
{
	vector_free(stack, string_free_void);
}
