#include "error.h"
#include "builder.h"
#include "runner.h"
#include "runner_priv.h"
#include "walker.h"
#include "params.h"
#include "shell.h"
#include "sig.h"
#include <stdbool.h>

/*
Non-fatal errors must be handled in walkers.
Therefore, only fatal errors should bubble up to the main loop.
*/
void	runner_run(t_shell *shell)
{
	t_parser			*parser;
	const t_lr_machine	*machine;
	t_ast_root			ast_root;
	t_error				err;

	err = error(ERR_NO);
	ast_root_init(&ast_root);
	parser = &shell->builder.parser;
	machine = &shell->builder.lr_machine;
	while (err.type == ERR_NO)
	{
		err = sig_process();
		if (err.type == ERR_NO)
			err = build_ast(parser, machine, &ast_root);
		if (err.type == ERR_NO)
			err = sig_process();
		if (err.type == ERR_NO
			&& option_is_active_in(shell->params.options, OPT_NOEXEC) == false)
				err = walk(&shell->runner, &ast_root);
		if (err.type == ERR_NO)
			err = sig_process();
		err = error_priorize(err, params_reap(&shell->params));
		runner_handle_errors(shell, &err);
		ast_root_free(&ast_root);
	}
}
