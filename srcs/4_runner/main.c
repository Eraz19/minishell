#include "error.h"
#include "runner.h"
#include "builder.h"
#include "options.h"
#include "shell.h"
#include <stdbool.h>

void	runner_init(t_runner *runner)
{
	(void)runner;
	// TODO;
}

static inline t_error	runner_handle_builder_error(t_runner *runner, t_error err)
{
	t_scanner	*scanner;

	(void)runner;
	// TODO
	if (err.type != ERR_SYNTAX_INVALID)
		return (err);
	scanner = shell_get_scanner();
	if (!scanner)
		return (error(ERR_SHELL_NOT_FOUND));
	err = scanner_reset(scanner);
	if (err.type)
		return (error_print(err, "runner", "unable to reset scanner",
			NULL, NULL));
	err = builder_reset();
	if (err.type)
		return (error_print(err, "runner", "unable to reset builder",
			NULL, NULL));
	return (err);
}

t_error	runner_loop_cycle(t_runner *runner)
{
	t_ast_root	ast_root;
	t_error		err;

	err = builder_get_ast(&ast_root);
	if (err.type != ERR_NO)
	{
		err = runner_handle_builder_error(runner, err);
		if (err.type)
			return (ast_root_free(&ast_root), err);
	}
	// TODO: err = walk_ast(&ast_root);
	// TODO: err = runner_handle_walker_error(runner, err);
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
	if (is_interactive == false)
		return (runner_loop_cycle(runner));
	while (true)
	{
		err = runner_loop_cycle(runner);
		if (err.type)
			return (err);
	}
	return (error(ERR_NO));
}

void	runner_free(t_runner *runner)
{
	(void)runner;
	// TODO
}
