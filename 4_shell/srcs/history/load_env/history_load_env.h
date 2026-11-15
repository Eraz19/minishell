/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_load_env.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:09:12 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 17:09:13 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_LOAD_ENV_H
# define HISTORY_LOAD_ENV_H

# include "history.h"

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup history
 * @brief Resolves @c HISTSIZE into the adapter's @c max: unset, empty or
 *        non-numeric values yield unlimited; a numeric value is used
 *        as-is.
 *
 * @note POSIX.1-2024: a user-set @c HISTSIZE is the accessible limit;
 *       the >=128 floor only constrains the unset default and the
 *       implementation capacity (unbounded here).
 *
 * @param history Already initialized history state (borrowed).
 * @return @c ERR_NO, absorbed lanes included. Module-external errors
 *         (env — allocation @c ERR_LIBC today) bubble through unlisted;
 *         see the audit in @c history_error.c.
 */
t_error	load_history_max_size_env(t_history *history);

/**
 * @ingroup history
 * @brief Resolves the history file pathname into @c file.path:
 *        @c HISTFILE when set and non-empty, else @c HOME +
 *        @c "/.sh_history", else persistent history is disabled with a
 *        diagnostic and the pathname left empty.
 *
 * @note A set-but-empty @c HISTFILE is treated as unset (documented
 *       choice, matches historical practice).
 *
 * @param history Already initialized history state (borrowed).
 * @return @c ERR_NO on success or disabled lane. Module-produced
 *         failures: @c ERR_LIBC (failed default-pathname append).
 *         Module-external errors (env — allocation @c ERR_LIBC today)
 *         bubble through unlisted; see the audit in @c history_error.c.
 */
t_error	load_history_path_from_env(t_history *history);

#endif
