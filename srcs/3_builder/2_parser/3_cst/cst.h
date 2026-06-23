#ifndef CST_H
# define CST_H

# include "parser_stack_type.h"

t_error	cst_node_new(
	t_parser_stack_item *lhs,
	t_parser_stack_item *rhs,
	size_t rhs_len,
	t_rule_id rule_id);
void	cst_node_set_data(t_cst_node *node, void *data, t_cst_free_data free_f);
void	cst_node_free(t_cst_node **node);

#endif
