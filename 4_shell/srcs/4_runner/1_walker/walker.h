/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walker.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:23:53 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:31:34 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WALKER_H
# define WALKER_H

# include "cmd.h"

t_error	walk(t_runner *runner, t_ast_root *ast_root);
t_error	walk_command(t_runner *runner, t_ast_command *command, int *status);
t_error	walk_function(t_cmd *cmd, t_runner *runner, int *status);

#endif
