/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 12:23:33 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 12:23:34 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUNNER_H
# define RUNNER_H

# include "runner_type.h"
# include "ast.h"

// Life cycle

void	runner_init(t_runner *runner);
t_error	runner_load(
			t_runner *runner,
			t_runner *parent_runner,
			t_scan_mode mode,
			const char *input);
void	runner_clear(t_runner *runner);
void	runner_free(t_runner *runner);
void	runner_free_void(void *runner);

// Ops

// TODO: doc
t_error	runner_run(t_runner *runner);
t_error	runner_run_ast(t_runner *runner, t_ast_root *ast_root);

#endif
