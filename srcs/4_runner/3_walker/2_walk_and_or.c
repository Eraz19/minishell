#include "error.h"
#include "walker_priv.h"

t_error	walk_and_or(t_runner *runner, t_ast_and_or *and_or, int *exit_status)
{
	size_t			i;
	t_ast_pipeline	*pipeline;
	t_error			err;

	i = 0;
	while (i < and_or->pipelines.len)
	{
		// TODO: next_on_success
		pipeline = &((t_ast_pipeline *)and_or->pipelines.data)[i];
		err = walk_pipeline(runner, pipeline, exit_status);
		if (err.type)
			return (err);
		i++;
	}
	return (error(ERR_NO));
}
