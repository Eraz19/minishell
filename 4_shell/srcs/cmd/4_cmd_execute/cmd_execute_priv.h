/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execute_priv.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:56:48 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:03:38 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_EXECUTE_PRIV_H
# define CMD_EXECUTE_PRIV_H

# include "cmd.h"

t_error	exec_builtin(t_cmd *cmd, int *exit_status);
t_error	exec_external(t_cmd *cmd, int *exit_status);

#endif
