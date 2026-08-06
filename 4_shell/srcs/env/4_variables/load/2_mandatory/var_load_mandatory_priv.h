/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_load_mandatory_priv.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:10:52 by gastesan          #+#    #+#             */
/*   Updated: 2026/08/06 14:10:53 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VAR_LOAD_MANDATORY_PRIV_H
# define VAR_LOAD_MANDATORY_PRIV_H

# include "error.h"

/**
 * @brief Set the IFS mandatory variable.
 *
 * @return @c ERR_VAR_INVALID_NAME, @c ERR_VAR_READ_ONLY or @c ERR_LIBC.
 */
t_error	var_set_ifs(void);

/**
 * @brief Validate whether a PWD value is acceptable.
 *
 * @param pwd Candidate PWD value (borrowed, read-only).
 * @param res Receives the validation result (borrowed).
 * @return @c ERR_LIBC.
 */
t_error	var_pwd_is_valid(const char *pwd, bool *res);

/**
 * @brief Set the PWD mandatory variable.
 *
 * @return @c ERR_VAR_INVALID_NAME, @c ERR_VAR_READ_ONLY or @c ERR_LIBC.
 */
t_error	var_set_pwd(void);

/**
 * @brief Set the PPID mandatory variable.
 *
 * @return @c ERR_VAR_INVALID_NAME, @c ERR_VAR_READ_ONLY or @c ERR_LIBC.
 */
t_error	var_set_ppid(void);

#endif
