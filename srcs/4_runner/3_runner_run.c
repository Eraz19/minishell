#include "error.h"
#include "builder.h"
#include "runner.h"
#include "runner_priv.h"
#include "walker.h"
#include "params.h"
#include "shell.h"
#include <stdbool.h>

/*
Non-fatal errors should be handled in walkers.
Therefore, only fatal errors should bubble up to the main loop.
*/
t_error	runner_run(t_shell *shell)
{
	t_ast_root	ast_root;
	t_error		err;

	err = error(ERR_NO);
	ast_root_init(&ast_root);
	while (err.type == ERR_NO)
	{
		err = builder_get_ast(&ast_root);
		if (err.type == ERR_NO)
			err = walk(&shell->runner, &ast_root);
		err = error_priorize(err, params_reap(&shell->params));
		runner_handle_errors(shell, &err);
		ast_root_free(&ast_root);
	}
	return (err);
}
