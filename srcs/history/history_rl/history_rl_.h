/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_rl_.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 15:17:54 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/12 14:09:35 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_RL__H
# define HISTORY_RL__H

# include "error.h"
# include "history_list_.h"

/**
 * @ingroup history
 * @struct s_history_rl
 * @brief Bookkeeping for the entries mirrored into readline's history.
 *
 * readline keeps its own private copies of the strings it is given; this
 * structure only tracks how many entries were mirrored and the cap to honour.
 *
 * @var s_history_rl::err Last error recorded while mirroring.
 * @var s_history_rl::max Maximum number of entries to keep, or -1 for
 *                        unlimited.
 * @var s_history_rl::count Number of entries currently mirrored in readline.
 */
typedef struct s_history_rl
{
	t_error	err;
	ssize_t	max;
	size_t	count;
}	t_history_rl;

/**
 * @ingroup history
 * @brief Initialises the readline bookkeeping.
 *
 * @param state Pointer to the readline bookkeeping (borrowed).
 */
void	history_rl_init(t_history_rl *state);

/**
 * @ingroup history
 * @brief Clears readline's history and resets the mirrored count.
 *
 * @param state Pointer to the readline bookkeeping (borrowed).
 */
void	history_rl_free(t_history_rl *state);

/**
 * @ingroup history
 * @brief Mirrors the whole entry list into readline.
 *
 * @param state Pointer to the readline bookkeeping (borrowed).
 * @param list Entry list to mirror (borrowed; copied out, never owned).
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	history_rl_load(t_history_rl *state, t_history_list *list);

/**
 * @ingroup history
 * @brief Computes how many of the last entries readline should add.
 *
 * Returns @p count when below the cap. A negative result signals that the
 * readline history must be cleared first because the cap was reached; its
 * magnitude is the number of entries to re-add.
 *
 * @param state Pointer to the readline bookkeeping (borrowed).
 * @param count Number of new entries being considered.
 * @return The count to add, negated when a clear-and-refill is required.
 */
ssize_t	history_rl_to_add_count(t_history_rl *state, size_t count);

/**
 * @ingroup history
 * @brief Adds the last @p count list entries to readline.
 *
 * Honours the cap (clearing and refilling when it is reached). Each entry is
 * deep copied out of the list and copied again by readline, so the list keeps
 * ownership of its data.
 *
 * @param state Pointer to the readline bookkeeping (borrowed).
 * @param list Entry list to read from (borrowed).
 * @param count Number of trailing entries to add.
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	history_rl_add(t_history_rl *state, t_history_list *list, size_t count);

#endif
