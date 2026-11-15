/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walk_pipeline_priv.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:23:19 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:25:12 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WALK_PIPELINE_PRIV_H
# define WALK_PIPELINE_PRIV_H

# define READ_ID	0
# define WRITE_ID	1

# include "ast.h"
# include "runner_type.h"

typedef struct s_pipe_run
{
	t_runner		*runner;
	t_ast_pipeline	*pipeline;
	size_t			command_id;
	int				pipe_fds[2];
	int				cmd_fds[2];
	int				last_failure;
	bool			pipefail_is_active;
	pid_t			*pids;
	int				exit_status;
}	t_pipe_run;

/* -------------------- life_cycle.c -------------------- */

void	walk_pipe_init(
			t_pipe_run *run,
			t_runner *runner,
			t_ast_pipeline *pipeline);
t_error	walk_pipe_spawn(
			t_runner *runner,
			t_ast_pipeline *pipeline,
			t_pipe_run *run);
void	walk_pipe_free(t_pipe_run *run);

/* -------------------- fds.c -------------------- */

t_error	walk_pipe_close_fd(t_pipe_run *run, int fd);
t_error	walk_pipe_close_all_fds(t_pipe_run *run);
t_error	walk_pipe_next_pipe(t_pipe_run *run);

/* -------------------- single_command.c -------------------- */

t_error	walk_pipe_single_command(
			t_runner *runner,
			t_ast_pipeline *pipeline,
			int *exit_status);

/* -------------------- multiple_commands.c -------------------- */

t_error	walk_pipe_multiple_commands(
			t_runner *runner,
			t_ast_pipeline *pipeline,
			int *exit_status);

/* -------------------- finalize.c -------------------- */

t_error	walk_pipe_finalize(t_pipe_run *run);

#endif
