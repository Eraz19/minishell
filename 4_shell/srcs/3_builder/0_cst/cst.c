/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:06:23 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 22:44:20 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "parser_item_stack_type.h"
#include "cst_type.h"
#include <stdlib.h>

static inline t_error	cst_node_set_children(
							t_cst_node *node,
							t_parser_item *rhs,
							size_t rhs_len)
{
	size_t	i;

	node->child_count = rhs_len;
	if (node->child_count == 0)
	{
		node->children = NULL;
		return (error(ERR_NO));
	}
	node->children = malloc(node->child_count * sizeof(*node->children));
	if (!node->children)
		return (error_sys());
	i = 0;
	while (i < node->child_count)
	{
		node->children[i] = rhs[i].cst_node;
		rhs[i].cst_node = NULL;
		i++;
	}
	return (error(ERR_NO));
}

t_error	cst_node_new(
			t_parser_item *lhs,
			t_parser_item *rhs,
			size_t rhs_len,
			t_rule_id rule_id)
{
	t_cst_node	*node;
	t_error		err;

	node = malloc(sizeof(*node));
	if (!node)
		return (error_sys());
	err = cst_node_set_children(node, rhs, rhs_len);
	if (err.type)
		return (free(node), err);
	node->symbol = lhs->symbol;
	node->rule_id = rule_id;
	node->tokens_start_id = lhs->tokens_start_id;
	node->tokens_count = lhs->tokens_count;
	(void)string_init(&node->heredoc_body, 0, NULL, 0);
	lhs->cst_node = node;
	return (error(ERR_NO));
}

void	cst_node_free(t_cst_node **node)
{
	t_cst_node	*tmp;
	size_t		i;

	if (!node || !*node)
		return ;
	tmp = *node;
	i = 0;
	while (i < tmp->child_count)
		cst_node_free(&tmp->children[i++]);
	free(tmp->children);
	string_free(&tmp->heredoc_body);
	free(tmp);
	*node = NULL;
}
