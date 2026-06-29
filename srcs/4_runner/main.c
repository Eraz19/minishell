#include "error.h"
#include "scanner.h"
#include "builder.h"
#include "runner.h"
#include "options.h"
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

static inline t_error	runner_loop_cycle(void)
{
	t_ast_root	ast_root;
	t_error		err;

	ast_root_init(&ast_root);
	err = builder_get_ast(&ast_root);
	// TODO: check error
	// TODO: err = walk_ast(&ast_root);
	// TODO: err = runner_handle_walker_error(runner, err);
	ast_root_free(&ast_root);
	return (err);
}

# include <stdio.h>	// DEBUG
# include "logs.h"	// DEBUG
t_error	runner_run(void)
{
	bool	is_interactive;
	t_error	err;

	err = option_is_active(OPT_INTERACTIVE, &is_interactive);
	if (err.type)
		return (err);
	if (is_interactive)
		print_warn("[RUNNER] starting loop (interactive)\n");
	else
		print_warn("[RUNNER] starting loop (non-interactive)\n");
	while (err.type == ERR_NO)
	{
		err = runner_loop_cycle();
		fprintf(stderr, "[RUNNER] runner_loop_cycle() = %s\n", error_to_string(err));
		if (err.type == ERR_EOF)
		{
			if (is_interactive == false)
				return (error(ERR_NO));	
		} 
		else if (err.type && (err.type != ERR_SYNTAX_INVALID || is_interactive == false))
			return (err);
		err = reset_scanner_and_builder();
		fprintf(stderr, "[RUNNER] reset_scanner_and_builder() = %s\n", error_to_string(err));
	}
	return (err);
}
