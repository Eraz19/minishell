/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_load_mandatory.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:10:53 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:10:54 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VAR_LOAD_MANDATORY_H
# define VAR_LOAD_MANDATORY_H

# include "error.h"

/**
 * @brief Load the mandatory variables required by the shell.
 *
 * @return @c ERR_VAR_INVALID_NAME, @c ERR_VAR_READ_ONLY or @c ERR_LIBC.
 */
t_error	var_load_mandatory(void);

#endif
