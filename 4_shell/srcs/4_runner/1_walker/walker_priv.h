/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walker_priv.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:23:50 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:23:51 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WALKER_PRIV_H
# define WALKER_PRIV_H

# include "error.h"
# include "ast.h"
# include "runner_type.h"
# include "cmd.h"

/* -------------------- helpers -------------------- */

bool	walk_loop_must_continue(t_runner *runner, t_error *err);
bool	walk_loop_must_break(t_runner *runner, t_error *err);

/* -------------------- walkers -------------------- */

t_error	walk_simple_cmd(t_runner *runner, t_ast_scmd *command, int *status);
t_error	walk_pipeline(t_runner *runner, t_ast_pipeline *pipeline, int *status);
t_error	walk_and_or(t_runner *runner, t_ast_and_or *and_or, int *status);
t_error	walk_list(t_runner *runner, t_ast_list *list, int *status);
t_error	walk_if(t_runner *runner, t_ast_if *if_node, int *status);
t_error	walk_for(t_runner *runner, t_ast_for *for_clause, int *status);
t_error	walk_loop(t_runner *runner, t_ast_loop *loop, int *status);
t_error	walk_case(t_runner *runner, t_ast_case *case_clause, int *status);
t_error	walk_function(t_cmd *cmd, t_runner *runner, int *status);

#endif
