/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_priv.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:56:55 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 21:26:45 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_PRIV_H
# define CMD_PRIV_H

# include "cmd.h"

// @ret ERR_POSIX_CMD_NFOUND / ERR_POSIX_CMD_NEXC / ERR_LIBC
t_error	cmd_search(t_cmd *cmd, bool path_is_temporary);

#endif
