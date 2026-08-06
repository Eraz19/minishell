/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_parser_store_cst.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:07:09 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:12:44 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "parser_priv.h"
#ifdef DEBUG_PARSING
# include "debug.h"		// DEBUG
# include "logs.h"		// DEBUG
# include <stdio.h>		// DEBUG
#endif
#include <assert.h>	// DEBUG

t_error	parser_store_cst(t_parser *parser, t_parser_item *main_item)
{
	assert(parser != NULL);
	assert(main_item != NULL);
#ifdef DEBUG_PARSING
	fprintf(stderr, "[PARSER] ACCEPT =======> %s%s%s (token_start=%zu token_count=%zu)\n",
		GREEN, symbol_to_string(main_item->symbol), NC,
		main_item->tokens_start_id,
		main_item->tokens_count);
#endif
	parser->cst = main_item->cst_node;
	main_item->cst_node = NULL;
	if (parser->lookahead_raw_symbol == SYM_NEWLINE)
		return (parser_read_heredoc(parser));
	return (error(ERR_NO));
}
