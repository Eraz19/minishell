/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_parser_accept.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:07:07 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:10:42 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "parser_priv.h"
#include "parser_item_stack.h"

t_error	parser_accept(t_parser *parser)
{
	t_parser_item	*main_item;
	bool			is_eof;
	t_error			err;

	if (parser->lookahead_symbol == SYM_EOF)
		scanner_clear(&parser->scanner);
	is_eof = parser->lookahead_raw_symbol == SYM_EOF;
	parser->lookahead_raw_symbol = SYM_NONE;
	parser->lookahead_symbol = SYM_NONE;
	main_item = parser_item_stack_top(&parser->item_stack);
	err = parser_store_cst(parser, main_item);
	if (err.type == ERR_NO && is_eof && !parser->search_cmd_sub_end)
		return (error(ERR_EOF));
	return (err);
}
