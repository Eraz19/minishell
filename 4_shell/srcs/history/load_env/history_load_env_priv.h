/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_load_env_priv.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:09:10 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/05 18:59:50 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_LOAD_ENV_PRIV_H
# define HISTORY_LOAD_ENV_PRIV_H

# include <sys/types.h>
# include "history.h"

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup history
 * @brief Fetches the environment variable @p var_name into
 *        @c history->file.path; a lookup failure or an empty value is
 *        rejected and the pathname freed, so the next lane starts clean.
 *
 * @param history Already initialized history state; @c history->err
 *                receives the lookup result (borrowed).
 * @param var_name Environment variable name to fetch (borrowed,
 *                 read-only).
 * @return @c true when @c file.path holds a non-empty pathname;
 *         @c false otherwise — @c history->err then tells a lookup miss
 *         (@c ERR_VAR_NOT_FOUND) from a failure.
 */
bool	load_file_path(t_history *history, const char *var_name);

/**
 * @ingroup history
 * @brief Applies the unlimited fallback for a non-numeric @c HISTSIZE
 *        and logs the lane.
 *
 * @param history Already initialized history state (borrowed).
 */
void	load_max_size_invalid_value(t_history *history);

/**
 * @ingroup history
 * @brief Applies the unlimited fallback for an unset or empty
 *        @c HISTSIZE and logs the lane.
 *
 * @param history Already initialized history state (borrowed).
 */
void	load_max_size_unset_value(t_history *history);

/* ************************************************************************* */
/*                                 ERROR                                     */
/* ************************************************************************* */

/**
 * @ingroup history
 * @brief Prints the "no valid history file path found" diagnostic;
 *        @c ERR_HISTORY_DISABLED is printed, never returned.
 */
void	on_history_disabled_error(void);

#endif
