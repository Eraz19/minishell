/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_assign_priv.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:56:22 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:56:23 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_ASSIGN_PRIV_H
# define CMD_ASSIGN_PRIV_H

# include "error.h"
# include "token.h"
# include "expander.h"
# include "cmd.h"

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

t_error	cmd_assignment_check(const t_token *token);

t_error	cmd_assignment_expand(
			t_token *token,
			t_exp_flag flags,
			t_string *out_expanded,
			int *exit_status);

t_error	cmd_assignment_process(
			t_cmd *cmd,
			t_token *token,
			t_string *expanded,
			bool *out_path_is_temporary);

#endif
