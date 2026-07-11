#include "error.h"
#include "walker_priv.h"

t_error	walk_and_or(t_runner *runner, t_ast_and_or *and_or, int *exit_status)
{
	size_t			i;
	t_ast_pipeline	*pipeline;
	bool			next_on_success;
	t_error			err;

	i = 0;
	*exit_status = 0;
	err = error(ERR_NO);
	while (i < and_or->pipelines.len)
	{
		*exit_status = -1;
		pipeline = &((t_ast_pipeline *)and_or->pipelines.data)[i];
		err = walk_pipeline(runner, pipeline, exit_status);
		if (err.type || i == and_or->pipelines.len - 1)
			break ;
		next_on_success = ((bool *)and_or->next_on_success.data)[i];
		if (next_on_success == true && *exit_status != 0)
			break ;
		if (next_on_success == false && *exit_status == 0)
			break ;
		i++;
	}
	return (walk_normalize_output(err, NULL, exit_status));
}
