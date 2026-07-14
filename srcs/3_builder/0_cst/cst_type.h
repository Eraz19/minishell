#ifndef CST_TYPE_H
# define CST_TYPE_H

# include "libft.h"
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
	t_string			heredoc_body;
}	t_cst_node;

#endif
