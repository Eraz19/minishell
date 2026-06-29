#include "error.h"
#include "parser_stack_type.h"
#include "cst_type.h"
#include <stdlib.h>
# include <assert.h>	// DEBUG

static inline t_error	cst_node_set_children(
							t_cst_node *node,
							t_parser_stack_item *rhs,
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
			t_parser_stack_item *lhs,
			t_parser_stack_item *rhs,
			size_t rhs_len,
			t_rule_id rule_id)
{
	t_cst_node	*node;
	t_error		err;

	assert(lhs != NULL);
	assert(rhs != NULL);
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
	node->data = NULL;
	node->free_func = NULL;
	lhs->cst_node = node;
	return (error(ERR_NO));
}

static inline void	cst_node_free_data(t_cst_node *node)
{
	if (node->data && node->free_func)
		node->free_func(node->data);
	node->data = NULL;
}

void	cst_node_set_data(t_cst_node *node, void *data, t_cst_free_data free_f)
{
	if (node->data)
		cst_node_free_data(node);
	node->data = data;
	node->free_func = free_f;
}


void	cst_node_free(t_cst_node **node)
{
	t_cst_node	*tmp;
	size_t		i;

	assert(node != NULL);
	assert(node != NULL);
	if (!node || !*node)
		return ;
	tmp = *node;
	i = 0;
	while (i < tmp->child_count)
		cst_node_free(&tmp->children[i++]);
	free(tmp->children);
	cst_node_free_data(tmp);
	free(tmp);
	*node = NULL;
}
