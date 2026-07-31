#include "shell.h"
#include "runner_type.h"
#include "runner.h"
#include <stdlib.h>
#ifdef DEBUG_INSTANCES
# include "logs.h"
# include "debug.h"
#endif

t_error	shell_get_new_runner_priv(
			t_runner **out_runner_ptr,
			t_scan_mode mode,
			const char *input,
			const char *caller)
{
	t_shell		*shell;
	t_runner	*new_runner;
	t_error		err;

	shell = shell_get();
	if (shell == NULL)
		return (error_print(error(ERR_INTERNAL), "shell not found", NULL, NULL));
	new_runner = malloc(sizeof(*new_runner));
	if (new_runner == NULL)
		return (error_print(error_sys(), __func__, NULL, NULL));
	runner_init(new_runner);
	if (shell->runner == NULL)
		err = runner_load(new_runner, NULL, mode, input);
	else
		err = runner_load(new_runner, shell->last_runner, mode, input);
	if (err.type)
		return (free(new_runner), err);
	if (shell->runner == NULL)
		shell->runner = new_runner;
	if (shell->last_runner != NULL)
		shell->last_runner->child = new_runner;
	shell->last_runner = new_runner;
#ifdef DEBUG_INSTANCES
	dump_shell_instance(shell->last_runner, caller);
#else
	(void)caller;
#endif
	return (*out_runner_ptr = shell->last_runner, err);
}

t_error	shell_get_new_lexer_priv(
			t_lexer **out_lexer_ptr,
			t_scan_mode mode,
			const char *input,
			const char *caller)
{
	t_runner	*runner;
	t_error		err;

	err = shell_get_new_runner_priv(&runner, mode, input, caller);
	if (err.type)
		return (err);
	*out_lexer_ptr = &runner->parser.scanner.lexer;
	return (err);
}

t_error	shell_get_new_scanner_priv(
			t_scanner **out_scanner_ptr,
			t_scan_mode mode,
			const char *input,
			const char *caller)
{
	t_runner	*runner;
	t_error		err;

	err = shell_get_new_runner_priv(&runner, mode, input, caller);
	if (err.type)
		return (err);
	*out_scanner_ptr = &runner->parser.scanner;
	return (err);
}

t_error	shell_get_new_parser_priv(
			t_parser **out_parser_ptr,
			t_scan_mode mode,
			const char *input,
			const char *caller)
{
	t_runner	*runner;
	t_error		err;

	err = shell_get_new_runner_priv(&runner, mode, input, caller);
	if (err.type)
		return (err);
	*out_parser_ptr = &runner->parser;
	return (err);
}

t_error	shell_destroy_last_instance_priv(const char *caller)
{
	t_shell		*shell;
	t_runner	*victim;
	t_runner	*prev_runner;

#ifdef DEBUG_INSTANCES
	fprintf(stderr, YELLOW "[SHELL ] instance destroyed by %s()\n", caller);
#else
	(void)caller;
#endif
	shell = shell_get();
	if (shell == NULL)
		return (error_print(error(ERR_INTERNAL), "shell not found", NULL, NULL));
	if (shell->last_runner == NULL)
		return (error_print(error(ERR_INTERNAL), "no shell instance", NULL, NULL));
	victim = shell->last_runner;
	prev_runner = victim->parent;
	runner_free(victim);
	free(victim);
	shell->last_runner = prev_runner;
	if (prev_runner == NULL)
		shell->runner = NULL;
	else
		prev_runner->child = NULL;
	return (error(ERR_NO));
}

