/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_shell_get_new.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:02:26 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 20:51:46 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	t_runner	*victim;
	t_runner	*prev_runner;

	shell = shell_get();
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
