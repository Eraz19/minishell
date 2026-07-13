#ifndef HISTORY_READLINE__H
# define HISTORY_READLINE__H

# include "error.h"
# include "history_list_.h"

/** @defgroup history_readline History readline mirror
 *  @brief Mirrors the entry list into readline's private history.
 *
 *  readline keeps its own private copies of the strings it is given: the
 *  entry list always keeps ownership of its data.
 */

/**
 * @ingroup history_readline
 * @struct s_history_rl
 * @brief Bookkeeping for the entries mirrored into readline's history.
 *
 * @var s_history_rl::err Last error recorded while mirroring.
 * @var s_history_rl::max Maximum number of entries to keep, @c -1 for
 *                        unlimited (from @c $HISTSIZE).
 * @var s_history_rl::count Number of entries currently mirrored in
 *                          readline.
 */
typedef struct s_history_rl
{
	t_error	err;
	ssize_t	max;
	size_t	count;
}	t_history_rl;

/* ************************************************************************* */
/*                                LIFE_CYCLE                                 */
/* ************************************************************************* */

/**
 * @ingroup history_readline
 * @brief Resets the mirrored count of @p state.
 *
 * @param state Readline bookkeeping initialized by the function
 *              (borrowed).
 */
void	history_rl_init(t_history_rl *state);

/**
 * @ingroup history_readline
 * @brief Mirrors the whole entry list into readline.
 *
 * @param state Already initialized readline bookkeeping (borrowed).
 * @param list Entry list to mirror (borrowed, read-only).
 * @return @c ERR_EMPTY_STACK or @c ERR_INDEX_OUT_OF_BOUND if an entry
 *         lookup fails, @c ERR_NO on success.
 */
t_error	history_rl_load(t_history_rl *state, t_history_list *list);

/**
 * @ingroup history_readline
 * @brief Clears readline's private history and resets the mirrored count.
 *
 * @param state Already initialized readline bookkeeping (borrowed).
 */
void	history_rl_free(t_history_rl *state);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup history_readline
 * @brief Re-mirrors the tail of @p list into readline, honouring the cap:
 *        readline's history is cleared then refilled with the last
 *        entries (all of them when the cap is unlimited).
 *
 * @note Entries are handed to readline as borrowed C-strings; readline
 *       copies them, the list keeps ownership.
 * @param state Already initialized readline bookkeeping (borrowed).
 * @param list Entry list to read from (borrowed, read-only).
 * @param count Number of new entries being considered; @c 0 is a no-op.
 * @return @c ERR_EMPTY_STACK or @c ERR_INDEX_OUT_OF_BOUND if an entry
 *         lookup fails, @c ERR_NO on success.
 */
t_error	history_rl_add(t_history_rl *state, t_history_list *list, size_t count);

/**
 * @ingroup history_readline
 * @brief Computes how many of the last entries readline should add.
 *
 * Returns @p count when below the cap. A negative result signals that the
 * readline history must be cleared first because the cap was reached; its
 * magnitude is the number of entries to re-add.
 *
 * @note Currently unused: @c history_rl_add always clears and refills.
 * @param state Already initialized readline bookkeeping
 *              (borrowed, read-only).
 * @param count Number of new entries being considered.
 * @return The count to add, negated when a clear-and-refill is required.
 */
ssize_t	history_rl_to_add_count(t_history_rl *state, size_t count);

#endif
