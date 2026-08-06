/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_resolve_priv.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:56:14 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 13:57:56 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_RESOLVE_PRIV_H
# define CMD_RESOLVE_PRIV_H

# include "cmd.h"

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

bool	cmd_resolve_is_declaration_utility(const char *name);
bool	cmd_resolve_is_special_builtin(t_cmd *cmd);
bool	cmd_resolve_is_function(t_cmd *cmd);
bool	cmd_resolve_is_intrinsic_builtin(t_cmd *cmd);

/**
 * @brief Warn when @p name matches a command name with unspecified POSIX
 *        resolution semantics.
 *
 * @note The warning is emitted only for names listed by POSIX 2.9.1.4 as
 *       producing unspecified results when used as command names.
 *
 * @param name Command name to inspect (borrowed, read-only).
 */
void	cmd_resolve_warn_if_unspecified(const char *name);

#endif
