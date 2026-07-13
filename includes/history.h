#ifndef HISTORY_H
# define HISTORY_H

# include "error.h"
# include "libft.h"
# include "history_list_.h"
# include "history_file_.h"
# include "history_readline_.h"

/** @defgroup history History API
 *  @brief Command history: in-memory list, readline mirror and
 *         persistent file.
 *
 *  The reader records every prompted line into the current entry; a
 *  completed entry joins the in-memory list and the readline history. At
 *  startup the persistent file (@c $HISTFILE, or @c $HOME/.sh_history) is
 *  loaded up to @c $HISTSIZE entries (values below 128 are raised to 128
 *  per XBD); at exit the new entries are appended back to it.
 *
 *  ERROR CONTRACT
 *
 *  History must never disturb input reading: every persistent-file
 *  problem (missing path, unreadable or unwritable file) is printed at
 *  the most specific point as a @c persistent @c history @c disabled
 *  warning and degraded to @c ERR_NO. @c ERR_HISTORY_DISABLED never
 *  escapes the module. @c ERR_INTERRUPTED is never degraded: a signal is
 *  control flow, not a persistence problem.
 *
 *  The module has two API surfaces:
 *  - Reader side (@ref history_save_entry,
 *    @ref history_append_to_entry): errors stay SPECIFIC, they cross the
 *    scanner API whose endpoints are the requalifiers.
 *  - Shell side (@ref history_load, @ref history_save): the callers no
 *    longer need specifics, so these endpoints requalify through
 *    @c history_error_qualify (see history_.h): @c ERR_LIBC printed and
 *    kept, other unqualified errors printed and requalified as
 *    @c ERR_INTERNAL.
 *
 *  @warning @c shell_run currently returns @ref history_save's error as
 *           the shell exit status: a failed save at exit overrides the
 *           real status. The shell loop should print and drop it.
 *  @warning A signal during the startup history-file read is degraded to
 *           a disabled warning instead of propagating
 *           @c ERR_INTERRUPTED: the read helper cannot distinguish a
 *           signal from a read failure through its boolean API.
 */

/**
 * @ingroup history
 * @struct s_history
 * @brief Aggregate state of the history module.
 *
 * @var s_history::err Last error recorded by the module.
 * @var s_history::file Persistent file backing, managed by the
 *                      history_file submodule.
 * @var s_history::list In-memory entries, managed by the history_list
 *                      submodule.
 * @var s_history::rl_history Readline mirror bookkeeping, managed by the
 *                            history_readline submodule.
 * @var s_history::current_input Line(s) of the entry being typed, a
 *                               @ref t_string owned by the module.
 */
typedef struct s_history
{
	t_error			err;
	t_history_file	file;
	t_history_list	list;
	t_history_rl	rl_history;
	t_string		current_input;
}	t_history;

/* ************************************************************************* */
/*                                LIFE_CYCLE                                 */
/* ************************************************************************* */

/**
 * @ingroup history
 * @brief Zeroes @p state and initializes its list, file backing,
 *        readline bookkeeping and current entry.
 *
 * @param state History state initialized by the function (borrowed).
 */
void	history_init(t_history *state);

/**
 * @ingroup history
 * @brief Resolves the history file path and size cap from the
 *        environment, loads the persistent entries and mirrors them into
 *        readline (shell side, qualified).
 *
 * @param state Already initialized history state (borrowed).
 * @return @c ERR_LIBC (printed) on system failure; @c ERR_INTERRUPTED
 *         when a signal interrupts a file operation; @c ERR_INTERNAL
 *         (printed) on internal inconsistency; @c ERR_NO on success or
 *         when persistence is disabled (printed warning).
 */
t_error	history_load(t_history *state);

/**
 * @ingroup history
 * @brief Frees the list, file backing, readline mirror and current entry
 *        of @p state, then zeroes it.
 *
 * @param state Already initialized history state (borrowed).
 */
void	history_free(t_history *state);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup history
 * @brief Appends @p entry to the entry currently being typed (reader
 *        side, raw errors).
 *
 * Operates on the global shell history state.
 *
 * @param entry Text to append (borrowed, read-only).
 * @return @c ERR_SHELL_NOT_FOUND if the shell data is unavailable,
 *         @c ERR_LIBC on allocation failure, @c ERR_NO on success.
 */
t_error	history_append_to_entry(t_string *entry);

/**
 * @ingroup history
 * @brief Appends the entries newer than the loaded prefix, plus the entry
 *        being typed, to the persistent file (shell side, qualified).
 *
 * Operates on the global shell history state.
 *
 * @return @c ERR_LIBC (printed) on system failure; @c ERR_INTERRUPTED
 *         when a signal interrupts the write; @c ERR_INTERNAL (printed)
 *         on internal inconsistency; @c ERR_NO on success or when
 *         persistence is disabled (printed warning).
 */
t_error	history_save(void);

/**
 * @ingroup history
 * @brief Completes the entry being typed: strips its trailing newline,
 *        stores it in the list and mirrors it into readline; empty
 *        entries are discarded (reader side, raw errors).
 *
 * Operates on the global shell history state.
 *
 * @note The no-op paths return the module's recorded error: a previously
 *       recorded hard failure is reported again (sticky module error).
 * @return @c ERR_SHELL_NOT_FOUND if the shell data is unavailable,
 *         @c ERR_LIBC on allocation failure, @c ERR_NO on success.
 */
t_error	history_save_entry(void);

#endif
