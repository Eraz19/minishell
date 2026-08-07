/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_cmd_sub_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:07:02 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:07:03 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_sub_priv.h"
#include "posix_helpers.h"
#include "runner.h"
#include "shell.h"
#include <stdlib.h>
#include <unistd.h>

#define CMD_SUB_PREFIX	"cmd sub"
#define SHELL_NF		"shell not found"

static inline void	cmd_sub_child_exit(
						t_error err,
						int status,
						t_ast_root *ast_root,
						t_string *cmd_string)
{
	if (ast_root != NULL)
		ast_root_free(ast_root);
	if (cmd_string != NULL)
		string_free(cmd_string);
	shell_free_void();
	if (err.type)
		exit((int)error_print(err, CMD_SUB_PREFIX, NULL, NULL).type);
	exit(status);
}

static inline t_error	cmd_sub_child_dup_and_close(int pipe_fds[2])
{
	t_error	err;

	err = posix_close_if_open(pipe_fds[0]);
	if (err.type)
		return (error_priorize(err, posix_close_if_open(pipe_fds[1])));
	if (pipe_fds[1] == STDOUT_FILENO)
		return (err);
	err = posix_dup2(pipe_fds[1], STDOUT_FILENO);
	if (err.type)
		return (error_priorize(err, posix_close_if_open(pipe_fds[1])));
	return (posix_close_if_open(pipe_fds[1]));
}

void	cmd_sub_child_string(t_string *cmd_string, int pipe_fds[2])
{
	t_runner	*runner;
	int			exit_status;
	t_error		err;

	err = cmd_sub_child_dup_and_close(pipe_fds);
	if (err.type)
		cmd_sub_child_exit(err, (int)err.type, NULL, cmd_string);
	err = shell_init_subshell(SUBSHELL_NORMAL);
	if (err.type)
		cmd_sub_child_exit(err, (int)err.type, NULL, cmd_string);
	err = shell_get_new_runner(&runner, SCAN_MODE_STRING, cmd_string->data);
	if (err.type)
		cmd_sub_child_exit(err, (int)err.type, NULL, cmd_string);
	err = runner_run(runner, false);
	err = error_priorize(err, shell_destroy_last_instance());
	if (err.type == ERR_EOF || err.type == ERR_VEOF)
		err.type = ERR_NO;
	else if (err.type)
		cmd_sub_child_exit(err, (int)err.type, NULL, cmd_string);
	err = env_get_last_status(&exit_status);
	cmd_sub_child_exit(err, exit_status, NULL, cmd_string);
}

void	cmd_sub_child_ast(t_ast_root *ast_root, int pipe_fds[2])
{
	t_runner	*runner;
	int			exit_status;
	t_error		err;

	err = cmd_sub_child_dup_and_close(pipe_fds);
	if (err.type)
		cmd_sub_child_exit(err, (int)err.type, ast_root, NULL);
	err = shell_init_subshell(SUBSHELL_NORMAL);
	if (err.type)
		cmd_sub_child_exit(err, (int)err.type, ast_root, NULL);
	err = shell_get_new_runner(&runner, SCAN_MODE_NONE, NULL);
	if (err.type)
		cmd_sub_child_exit(err, (int)err.type, ast_root, NULL);
	err = runner_run_ast(runner, ast_root);
	err = error_priorize(err, shell_destroy_last_instance());
	if (err.type)
		cmd_sub_child_exit(err, (int)err.type, ast_root, NULL);
	err = env_get_last_status(&exit_status);
	cmd_sub_child_exit(err, exit_status, ast_root, NULL);
}
