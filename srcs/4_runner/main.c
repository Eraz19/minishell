#include "error.h"
#include "runner.h"
#include "builder.h"
#include "options.h"
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
	// TODO
	return (false);
}

t_error	runner_loop_cycle(t_runner *runner)
{
	t_ast_root	ast_root;
	t_error		err;

	err = builder_get_ast(&ast_root);
	if (err.type != ERR_NO && !runner_continue_on_builder_error(runner, err))
		return (err);
	ast_root_free(&ast_root);
	// TODO: err = walk_ast(&ast_root);
	// TODO: handle non-fatal errors
	// TODO: ast_free_node(&ast_root);
	return (error(ERR_NO));
}

t_error	runner_run(t_runner *runner)
{
	t_error	err;

	if (!option_is_active(OPT_INTERACTIVE))
		return (runner_loop_cycle(runner));
	while (true)
	{
		err = runner_loop_cycle(runner);
		if (err.type)
			return (err);
	}
}

void	runner_free(t_runner *runner)
{
	(void)runner;
	// TODO
}
