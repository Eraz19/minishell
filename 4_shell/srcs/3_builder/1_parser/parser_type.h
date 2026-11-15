/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_type.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:07:17 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:07:18 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_TYPE_H
# define PARSER_TYPE_H

# include "grammar_symbols.h"
# include "lr_tables.h"
# include "parser_item_stack_type.h"
# include "parser_here_stack_type.h"
# include "token_pool.h"
# include "scanner.h"

typedef struct s_parser
{
	t_scanner			scanner;
	const t_lr_tables	*tables;				// borrowed
	t_parser_item_stack	item_stack;
	t_parser_here_stack	here_stack;
	t_token_pool		token_pool;
	size_t				lookahead_id;
	t_symbol			lookahead_raw_symbol;
	t_symbol			lookahead_symbol;
	t_cst_node			*cst;					// owned
	bool				search_cmd_sub_end;
	ssize_t				cmd_sub_end_index;
}	t_parser;

#endif
