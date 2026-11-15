/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_parser_store_cst.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:07:09 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 20:54:19 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "parser_priv.h"

t_error	parser_store_cst(t_parser *parser, t_parser_item *main_item)
{
	parser->cst = main_item->cst_node;
	main_item->cst_node = NULL;
	if (parser->lookahead_raw_symbol == SYM_NEWLINE)
		return (parser_read_heredoc(parser));
	return (error(ERR_NO));
}
