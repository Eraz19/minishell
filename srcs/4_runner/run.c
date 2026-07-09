#include "error.h"
#include "scanner.h"
#include "builder.h"
#include "runner.h"
#include "options.h"
#include "walker.h"
#include <stdbool.h>

static inline t_error	reset_scanner_and_builder(void)
{
	t_error	err;
	
	err = scanner_reset();
	if (err.type)
		return (error_print(err, "runner", "unable to reset scanner",
			NULL, NULL));
	err = builder_reset();
	if (err.type)
		return (error_print(err, "runner", "unable to reset builder",
			NULL, NULL));
	return (err);
}

# include <stdio.h>
static inline t_error	runner_loop_cycle(t_runner *runner)
{
	t_ast_root	ast_root;
	t_error		err;

	ast_root_init(&ast_root);
	err = builder_get_ast(&ast_root);
	if (err.type == ERR_NO)
		err = walk(runner, &ast_root);
	// TODO: handle errors directly in walker / executor
	if (err.type == ERR_POSIX_CMD_NOT_EXECUTABLE || err.type == ERR_POSIX_CMD_NOT_EXECUTABLE)
		err = error(ERR_NO);
	ast_root_free(&ast_root);
	return (err);
}

t_error	runner_run(t_runner *runner)
{
	bool	is_interactive;
	t_error	err;

	err = option_is_active(OPT_INTERACTIVE, &is_interactive);
	if (err.type)
		return (err);
	while (err.type == ERR_NO)
	{
		err = runner_loop_cycle(runner);
		if (err.type == ERR_EOF)
		{
			if (is_interactive == false)
				return (error(ERR_NO));
			err = error(ERR_NO);
		} 
		else if (err.type && (err.type != ERR_POSIX_SYNTAX || is_interactive == false))
			return (err);
		if (err.type == ERR_POSIX_SYNTAX)
			err = reset_scanner_and_builder();
		else if (err.type)
			return (err);
	}
	return (err);
}
