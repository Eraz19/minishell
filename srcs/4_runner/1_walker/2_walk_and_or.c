#include "error.h"
#include "walker_priv.h"
# include <assert.h>

static inline size_t	walk_and_or_next_index(
							t_ast_and_or *and_or,
							size_t i,
							int exit_status)
{
	bool	next_on_success;

	while (i < and_or->next_on_success.len)
	{
		next_on_success = ((bool *)and_or->next_on_success.data)[i];
		i++;
		if (next_on_success == true && exit_status == 0)
			return (i);
		else if (next_on_success == false && exit_status != 0)
			return (i);
	}
	return (and_or->pipelines.len);
}

t_error	walk_and_or(t_runner *runner, t_ast_and_or *and_or, int *exit_status)
{
	size_t			i;
	t_ast_pipeline	*pipeline;
	t_error			err;

	assert(and_or->pipelines.len > 0);
	assert(and_or->next_on_success.len == and_or->pipelines.len - 1);
	i = 0;
	err = error(ERR_NO);
	while (i < and_or->pipelines.len)
	{
		pipeline = &((t_ast_pipeline *)and_or->pipelines.data)[i];
		err = walk_pipeline(runner, pipeline, exit_status);
		if (err.type || i == and_or->pipelines.len - 1)
			break ;
		i = walk_and_or_next_index(and_or, i, *exit_status);
	}
	return (err);
}
