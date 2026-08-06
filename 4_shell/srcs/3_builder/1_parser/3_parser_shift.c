/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_parser_shift.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:07:04 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:07:05 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "parser_priv.h"
#include "cst.h"
#include <assert.h>	// DEBUG

static inline bool	parser_is_reducing_cmd_sub(
						const t_parser *parser,
						size_t lr_state_id)
{
	const t_action	*action;

	if (parser->search_cmd_sub_end == false
		|| parser->lookahead_symbol != SYM_RPARENTHESIS)
		return (false);
	action = &parser->tables->actions[lr_state_id * ACTION_COL_COUNT + SYM_EOF];
	return (action->type == ACTION_REDUCE && action->payload == RULE_CMD_SUB);
}

static inline t_error	parser_add_item(t_parser *parser, size_t lr_state_id)
{
	t_parser_item	item;
	t_error			err;

	item.symbol = parser->lookahead_symbol;
	item.lr_state_id = lr_state_id;
	item.tokens_start_id = parser->lookahead_id;
	item.tokens_count = 1;
	err = cst_node_new(&item, NULL, 0, RULE_NONE);
	if (err.type)
		return (err);
	if (!vector_push(&parser->item_stack, &item))
	{
		err = error_sys();
		cst_node_free(&item.cst_node);
		return (parser_internal_error(err));
	}
	return (err);
}

static inline t_error	parser_add_item_and_inject_synthetic_eof(
							t_parser *parser,
							size_t lr_state_id)
{
	const t_token	*token;
	t_error			err;

	token = parser_get_token(parser, parser->lookahead_id);
	parser->cmd_sub_end_index = token->index.end;
	err = parser_add_item(parser, lr_state_id);
	if (err.type)
		return (err);
	parser->lookahead_raw_symbol = SYM_EOF;
	parser->lookahead_symbol = SYM_EOF;
	return (error(ERR_NO));
}

t_error	parser_shift(t_parser *parser, size_t lr_state_id)
{
	t_error			err;

	assert(parser != NULL);
	err = parser_read_heredoc(parser);
	if (err.type)
		return (err);
	if (parser_is_reducing_cmd_sub(parser, lr_state_id))
		return (parser_add_item_and_inject_synthetic_eof(parser, lr_state_id));
	err = parser_add_item(parser, lr_state_id);
	if (err.type)
		return (err);
	return (parser_read_next_symbol(parser, false));
}
