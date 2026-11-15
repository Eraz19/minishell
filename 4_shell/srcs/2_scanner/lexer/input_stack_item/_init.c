/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _init.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:12:04 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 16:12:05 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_input_stack_item.h"

void	lexer_input_stack_item_init(t_lexer_input_stack_item *item)
{
	*item = (t_lexer_input_stack_item){0};
	(void)string_init(&item->str, 0, NULL, 0);
}

void	lexer_input_stack_item_free(void *item)
{
	string_free(&((t_lexer_input_stack_item *)item)->str);
	((t_lexer_input_stack_item *)item)->i = 0;
	((t_lexer_input_stack_item *)item)->alias_position_exempt = false;
}
