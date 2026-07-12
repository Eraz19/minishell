#include "error.h"
#include "walker_priv.h"
# include <assert.h>

t_error	walk_if(t_runner *runner, t_ast_if *if_node, int *exit_status)
{
	size_t		i;
	t_ast_list	*condition;
	t_ast_list	*body;
	t_error		err;

	assert(if_node->conditions.len > 0);
	assert(if_node->conditions.len == if_node->bodies.len);
	i = 0;
	while (i < if_node->conditions.len)
	{
		condition = &((t_ast_list *)if_node->conditions.data)[i];
		err = walk_list(runner, condition, exit_status);
		if (err.type)
			return (err);
		else if (*exit_status == 0)
		{
			body = &((t_ast_list *)if_node->bodies.data)[i];
			return (walk_list(runner, body, exit_status));
		}
		i++;
	}
	if (if_node->has_else == true)
		return (walk_list(runner, &if_node->else_body, exit_status));
	*exit_status = 0;
	return (walk_normalize_output(err, NULL, exit_status));
}
