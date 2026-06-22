#include "error.h"
#include "runner.h"
#include "builder.h"
#include <stdbool.h>

void	runner_init(t_runner *runner)
{
	(void)runner;
	// TODO;
}

static bool	runner_continue_on_builder_error(t_runner *runner, t_error err)
{
	(void)runner;
	(void)err;
	return (true);
}

t_error	runner_loop(t_runner *runner)
{
	t_ast_node	*ast;
	t_error		err;

	while (true)
	{
		err = builder_get_ast(&ast);
		if (err.type != ERR_NO && !runner_continue_on_builder_error(runner, err))
			return (err);
		// TODO: execute
	}
}

void	runner_free(t_runner *runner)
{
	(void)runner;
	// TODO
}
