#include "builder.h"

t_error	parser_cst_node_new(
	t_stack_item *lhs,
	t_stack_item *rhs,
	size_t item_count,
	t_cst_node **dst)
{
	(void)lhs;
	(void)rhs;
	(void)item_count;
	*dst = NULL;
	// TODO
	return (error(ERR_NO));
}

void	parser_cst_node_free(t_cst_node **node)
{
	// TODO
	*node = NULL;
}
