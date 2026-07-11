#include "error.h"
#include "walker.h"
#include "walker_priv.h"

t_error	walk(t_runner *runner, t_ast_root *ast_root, int *exit_status)
{
	size_t			i;
	t_ast_and_or	*and_or;
	t_error			err;

	i = 0;
	while (i < ast_root->and_ors.len)
	{
		// TODO: subshell
		// TODO: async
		and_or = &((t_ast_and_or *)ast_root->and_ors.data)[i];
		err = walk_and_or(runner, and_or, exit_status);
		if (err.type)
			return (err);
		i++;
	}
	return (error(ERR_NO));
}
