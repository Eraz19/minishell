#ifndef HISTORY_H
# define HISTORY_H

# include "error.h"
# include "libft.h"
# include "history_list_.h"
# include "history_file_.h"
# include "history_readline_.h"

/** @defgroup history History API
 *  @brief Command history backed by a file, an in-memory list and readline.
 *
 *  Stores the shell command history and keeps full ownership of its data:
 *  every string that enters the module is deep copied, and every string that
 *  leaves it is a deep copy whose ownership passes to the caller, so no
 *  buffer is ever shared with the outside. The on-disk file and readline's
 *  own history are the only two channels through which entries cross the
 *  module boundary.
 */

/**
 * @ingroup history
 * @struct s_history
 * @brief Aggregate state of the history module.
 *
 * Groups the persistent file backing, the in-memory entry list, the readline
 * mirror and the buffer accumulating the line currently being typed.
 *
 * @var s_history::err Last error recorded by the module.
 * @var s_history::file On-disk history file (path and content buffer).
 * @var s_history::list In-memory list of history entries (owned).
 * @var s_history::rl_history Bookkeeping for readline's own history.
 * @var s_history::current_input Buffer holding the line being assembled.
 */
typedef struct s_history
{
	t_error			err;
	t_history_file	file;
	t_history_list	list;
	t_history_rl	rl_history;
	t_buff			current_input;
}	t_history;

/**
 * @ingroup history
 * @brief Initialises a history state to an empty, ready-to-use value.
 *
 * Zeroes the structure then initialises the entry list, the file backing,
 * the readline bookkeeping and the current-input buffer. Does not touch the
 * filesystem or readline; call history_load() to populate it.
 *
 * @param state Pointer to the history state to initialise (borrowed).
 */
void	history_init(t_history *state);

/**
 * @ingroup history
 * @brief Releases every resource held by a history state.
 *
 * Frees the entry list, the file content buffer and the current-input
 * buffer, clears readline's history, then resets the structure to zero.
 *
 * @param state Pointer to the history state to free (borrowed).
 */
void	history_free(t_history *state);

/**
 * @ingroup history
 * @brief Loads the history from its file into memory and readline.
 *
 * Resolves the file path from $HISTFILE (falling back to $HOME/.sh_history)
 * and the cap from $HISTSIZE, reads and parses the file into the entry list
 * (keeping at most $HISTSIZE entries) and mirrors the loaded entries into
 * readline. Each parsed entry is a fresh allocation owned by the module.
 *
 * @param state Pointer to an initialised history state (borrowed).
 * @return ERR_NO on success, or the error recorded in state->err.
 */
t_error	history_load(t_history *state);

/**
 * @ingroup history
 * @brief Appends to the file the entries added since the last load.
 *
 * Serialises every list entry recorded after the loaded prefix, appends the
 * currently typed line when it is non-empty, then writes the result to the
 * history file. Operates on the global shell history.
 *
 * @return ERR_NO on success, ERR_SHELL_NOT_FOUND if the shell history is
 *         unavailable, or the recorded error on failure.
 */
t_error	history_save(void);

/**
 * @ingroup history
 * @brief Commits the line being assembled as a new history entry.
 *
 * Trims a trailing newline from the current-input buffer, turns the
 * remaining text into a freshly owned entry, pushes it onto the list,
 * resets the buffer and mirrors the entry into readline. Does nothing when
 * the current input is empty or becomes empty after trimming. Operates on
 * the global shell history.
 *
 * @return ERR_NO on success, ERR_SHELL_NOT_FOUND if the shell history is
 *         unavailable, or the recorded error on failure.
 */
t_error	history_save_entry(void);

/**
 * @ingroup history
 * @brief Appends a fragment to the line currently being assembled.
 *
 * The fragment is deep copied into the current-input buffer, so the caller
 * keeps ownership of @p entry. Call history_save_entry() to commit the
 * assembled line. Operates on the global shell history.
 *
 * @param entry NUL-terminated fragment to append (borrowed; deep copied).
 * @return ERR_NO on success, ERR_SHELL_NOT_FOUND if the shell history is
 *         unavailable, or ERR_LIBC on allocation failure.
 */
t_error	history_append_to_entry(char *entry);

#endif
