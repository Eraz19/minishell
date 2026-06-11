/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_stack_.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 17:03:49 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/10 19:01:10 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_STACK__H
# define INPUT_STACK__H

# include "context.h"

typedef t_vector	t_input_stack;

typedef struct s_input_stack_item
{
	size_t			i;
	char			*str;
	t_context_stack	context;
}	t_input_stack_item;

void	input_stack_init(t_input_stack *stack);
void	input_stack_free(t_input_stack *stack);

void	input_stack_item_free(void *item);
void	input_stack_item_init(t_input_stack_item *item);

t_error	input_stack_pop(t_input_stack *stack);
t_error	input_stack_push(t_input_stack *stack, t_input_stack_item item);
t_error	input_stack_get_last(t_input_stack *stack, t_input_stack_item *item);

#endif
