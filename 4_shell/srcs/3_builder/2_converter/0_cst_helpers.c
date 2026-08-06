/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_cst_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:07:32 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:07:33 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "converter_priv.h"
#include "cst_type.h"
#include "token.h"
#include <stdbool.h>
#include <assert.h>	// DEBUG

static inline size_t	cst_token_id(const t_cst_node *node, size_t token_id)
{
	assert(node != NULL);
	assert(token_id < node->tokens_count);
	return (node->tokens_start_id + token_id);
}

t_token	*converter_get_token(
			const t_parser *parser,
			const t_cst_node *node,
			size_t node_token_id)
{
	size_t	token_id;

	assert(parser != NULL);
	token_id = cst_token_id(node, node_token_id);
	return (parser_get_token(parser, token_id));
}

void	converter_take_token(
			t_parser *parser,
			const t_cst_node *node,
			size_t node_token_id,
			t_token *dst)
{
	size_t	token_id;

	assert(parser != NULL);
	token_id = cst_token_id(node, node_token_id);
	parser_take_token(parser, token_id, dst);
}

t_error	converter_transfer_token(
			t_parser *parser,
			const t_cst_node *node,
			size_t node_token_id,
			t_token_pool *dst)
{
	size_t	token_id;

	assert(parser != NULL);
	token_id = cst_token_id(node, node_token_id);
	return (token_pool_transfer(dst, &parser->token_pool, token_id));
}
