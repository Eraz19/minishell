#ifndef CST_TYPE_H
# define CST_TYPE_H

# include "symbols_type.h"
# include "rules__type.h"
# include <stddef.h>

typedef void	(*t_cst_free_data)(void *data);

typedef struct s_cst_node
{
	t_symbol			symbol;
	t_rule_id			rule_id;
	size_t				tokens_start_id;
	size_t				tokens_count;
	struct s_cst_node	**children;
	size_t				child_count;
	void				*data;
	t_cst_free_data		free_func;
}	t_cst_node;

#endif
