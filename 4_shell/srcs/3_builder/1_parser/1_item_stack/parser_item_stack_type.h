/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_item_stack_type.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:06:46 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:06:47 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_ITEM_STACK_TYPE_H
# define PARSER_ITEM_STACK_TYPE_H

# include "grammar_symbols.h"
# include "libft.h"
# include "cst_type.h"
# include <stddef.h>

typedef struct s_parser_item
{
	t_symbol	symbol;
	size_t		lr_state_id;
	size_t		tokens_start_id;
	size_t		tokens_count;
	t_cst_node	*cst_node;
}	t_parser_item;

// vector of t_parser_item
typedef t_vector	t_parser_item_stack;

#endif
