/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_item_stack.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:06:51 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:15:54 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_ITEM_STACK_H
# define PARSER_ITEM_STACK_H

# include "parser_item_stack_type.h"

void			parser_item_stack_init(t_parser_item_stack *stack);
void			parser_item_stack_clear(t_parser_item_stack *stack);
void			parser_item_stack_free(t_parser_item_stack *stack);

t_parser_item	*parser_item_stack_top(const t_parser_item_stack *stack);

#endif
