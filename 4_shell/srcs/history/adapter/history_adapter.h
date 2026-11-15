/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_adapter.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:08:21 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 17:24:26 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_ADAPTER_H
# define HISTORY_ADAPTER_H

# include "history_list.h"

/* ************************************************************************* */
/*                                  TYPES                                    */
/* ************************************************************************* */

/**
 * @ingroup history
 * @struct s_history_adapter
 * @brief Bookkeeping for the readline history mirror.
 *
 * @var s_history_adapter::err Last error recorded by an adapter
 *                             operation (reserved, no producer yet).
 * @var s_history_adapter::max Maximum entries mirrored into readline
 *                             (user @c HISTSIZE); negative means
 *                             unlimited.
 * @var s_history_adapter::count Entries currently held by readline's
 *                               history.
 */
typedef struct s_history_adapter
{
	t_error	err;
	ssize_t	max;
	size_t	count;
}	t_history_adapter;

/* ************************************************************************* */
/*                                LIFE_CYCLE                                 */
/* ************************************************************************* */

/**
 * @ingroup history
 * @brief Resets @c err, sets @c max to unlimited and zeroes @c count.
 *
 * @param history_adapter Adapter state; initialized by the function
 *                        (borrowed).
 */
void	history_adapter_init(t_history_adapter *history_adapter);

/**
 * @ingroup history
 * @brief Mirrors the whole @p history_list into readline, trimmed to
 *        @c max.
 *
 * @param history_adapter Already initialized adapter state (borrowed).
 * @param history_list Entries to mirror (borrowed, read-only).
 */
void	history_adapter_load(
			t_history_adapter *history_adapter,
			t_history_list *history_list);

/**
 * @ingroup history
 * @brief Clears readline's history and zeroes @c count.
 *
 * @warning Affects the global readline state of the process.
 *
 * @param history_adapter Already initialized adapter state (borrowed).
 */
void	history_adapter_free(t_history_adapter *history_adapter);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup history
 * @brief Mirrors the last @p count entries of @p history_list into
 *        readline; when the mirror would exceed @c max, clears it and
 *        re-adds the newest @c max entries instead. A @p count of @c 0
 *        is a no-op.
 *
 * @param history_adapter Already initialized adapter state (borrowed).
 * @param history_list Source entries (borrowed, read-only).
 * @param count Number of newest entries to add incrementally.
 */
void	add_to_readline_history(
			t_history_adapter *history_adapter,
			t_history_list *history_list, size_t count);

#endif
