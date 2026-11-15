/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_life_cycle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:10:16 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 22:51:16 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "positionals.h"

void	positionals_init_stack(t_positionals_stack *stack)
{
	(void)vector_init(stack, sizeof(t_positionals), 0);
}

void	positionals_free_item(void *positionals)
{
	vector_free(positionals, string_free_void);
}

void	positionals_free_stack(t_positionals_stack *stack)
{
	vector_free(stack, positionals_free_item);
}

void	positionals_clear_stack(t_positionals_stack *stack)
{
	vector_clear(stack, positionals_free_item);
}
