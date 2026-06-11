/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 17:12:09 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/10 19:00:59 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "input_stack_.h"

void	input_stack_item_free(void *item)
{
	t_input_stack_item	*item_;

	item_ = (t_input_stack_item *)item;
	if (item_->str != NULL)
		free(item_->str);
	context_stack_free(&item_->context);
	*item_ = (t_input_stack_item){0};
}

void	input_stack_item_init(t_input_stack_item *item)
{
	*item = (t_input_stack_item){0};
	context_stack_init(&item->context);
}

void	input_stack_init(t_input_stack *stack)
{
	vector_init(stack, sizeof(t_input_stack_item), 0);
}

void	input_stack_free(t_input_stack *stack)
{
	vector_free(stack, input_stack_item_free);
}
