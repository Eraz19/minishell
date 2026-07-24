#include "shell.h"
#include "runner_type.h"
#include "runner.h"
#include <stdlib.h>

t_error	shell_get_new_runner(
			t_runner **out_runner_ptr,
			t_scan_mode mode,
			const char *input)
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
	return (*out_runner_ptr = shell->last_runner, err);
}

t_error	shell_get_new_lexer(
			t_lexer **out_lexer_ptr,
			t_scan_mode mode,
			const char *input)
{
	t_runner	*runner;
	t_error		err;

	err = shell_get_new_runner(&runner, mode, input);
	if (err.type)
		return (err);
	*out_lexer_ptr = &runner->parser.scanner.lexer;
	return (err);
}

t_error	shell_get_new_scanner(
			t_scanner **out_scanner_ptr,
			t_scan_mode mode,
			const char *input)
{
	t_runner	*runner;
	t_error		err;

	err = shell_get_new_runner(&runner, mode, input);
	if (err.type)
		return (err);
	*out_scanner_ptr = &runner->parser.scanner;
	return (err);
}

t_error	shell_get_new_parser(
			t_parser **out_parser_ptr,
			t_scan_mode mode,
			const char *input)
{
	t_runner	*runner;
	t_error		err;

	err = shell_get_new_runner(&runner, mode, input);
	if (err.type)
		return (err);
	*out_parser_ptr = &runner->parser;
	return (err);
}

t_error	shell_destroy_last_instance(void)
{
	t_shell		*shell;
	t_runner	*prev_runner;

	prev_runner = NULL;
	shell = shell_get();
	if (shell == NULL)
		return (error_print(error(ERR_INTERNAL), "shell not found", NULL, NULL));
	if (shell->last_runner == NULL)
		return (error_print(error(ERR_INTERNAL), "no shell instance", NULL, NULL));
	if (shell->last_runner->parent != NULL)
		prev_runner = shell->last_runner->parent;
	runner_free(shell->last_runner);
	shell->last_runner = prev_runner;
	return (error(ERR_NO));
}

