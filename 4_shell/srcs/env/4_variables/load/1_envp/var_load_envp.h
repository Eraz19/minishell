/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_load_envp.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:10:40 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:10:41 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VAR_LOAD_ENVP_H
# define VAR_LOAD_ENVP_H

# include "error.h"

/**
 * @brief Load variables from the environment vector.
 *
 * @param envp Environment vector (borrowed, read-only).
 * @return @c ERR_ASSIGNMENT_MISSING_NAME or @c ERR_LIBC.
 */
t_error	var_load_envp(char **envp);

#endif
