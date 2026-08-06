/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_here_stack.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:06:56 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:06:57 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_here_stack_type.h"
#include "parser_here_stack.h"
#include "cst_type.h"
#include <assert.h>	// DEBUG

void	parser_here_stack_init(t_parser_here_stack *stack)
{
	(void)vector_init(stack, sizeof(t_cst_node *), 0);
}

void	parser_here_stack_clear(t_parser_here_stack *stack)
{
	vector_clear(stack, NULL);
}

void	parser_here_stack_free(t_parser_here_stack *stack)
{
	vector_free(stack, NULL);
}

t_cst_node	*parser_here_stack_get(const t_parser_here_stack *stack, size_t i)
{
	assert(stack != NULL);
	assert(stack->len > 0);
	if (stack->len == 0)
		return (NULL);
	return (((t_cst_node **)stack->data)[i]);
}
