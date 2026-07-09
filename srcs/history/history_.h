#ifndef HISTORY__H
# define HISTORY__H

#include "history.h"

/** @defgroup history_priv History internals
 *  @brief Environment resolution, file-content building and error
 *         requalification behind the history API.
 */

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup history_priv
 * @brief Builds the file content from the persisted tail and pending
 *        input.
 *
 * Serializes and concatenates the list entries from index @p start
 * onward, then appends the currently typed line when it is non-empty,
 * into the file backing's content string, which is freed on failure.
 *
 * @param state History state (borrowed).
 * @param start Index of the first list entry to include.
 * @return @c ERR_LIBC on allocation failure, @c ERR_NO on success.
 */
t_error	history_build_file_content(t_history *state, size_t start);

/**
 * @ingroup history_priv
 * @brief Requalifies an error escaping the shell-facing history API
 *        (@c history_load, @c history_save), whose callers no longer need
 *        the specifics.
 *
 * Prints the specific diagnostic at the moment precision is lost, then
 * requalifies: any unqualified error becomes @c ERR_INTERNAL.
 * @c ERR_LIBC is printed with the history context and kept, fully
 * qualified errors (>= @c ERR_INTERRUPTED) pass through untouched.
 *
 * @note The reader-facing endpoints (@c history_save_entry,
 *       @c history_append_to_entry) must NOT use it: their errors cross
 *       the scanner API, whose endpoints are the requalifiers.
 *
 * @param err Error to requalify.
 * @return The requalified (and printed) error.
 */
t_error	history_error_qualify(t_error err);

/**
 * @ingroup history_priv
 * @brief Resolves the history file path from the environment.
 *
 * Reads @c $HISTFILE when it is set and non-empty, otherwise falls back
 * to @c $HOME/.sh_history when @c HOME is available. If neither variable
 * yields a usable path, leaves the file path empty, prints a
 * @c persistent @c history @c disabled warning and reports success.
 *
 * @param state History state; its file path string is initialized by the
 *              function (borrowed).
 * @return @c ERR_SHELL_NOT_FOUND if the shell parameters are unavailable,
 *         @c ERR_LIBC on allocation failure, @c ERR_NO on success or when
 *         persistence is disabled.
 */
t_error	history_load_path_env(t_history *state);

/**
 * @ingroup history_priv
 * @brief Resolves the history size cap from the environment.
 *
 * Reads @c $HISTSIZE into the readline bookkeeping's cap. An unset or
 * empty value means unlimited (@c -1); any non-negative value below 128
 * is raised to 128 (XBD minimum).
 *
 * @param state History state (borrowed).
 * @return @c ERR_SHELL_NOT_FOUND if the shell parameters are unavailable,
 *         @c ERR_LIBC on allocation failure, @c ERR_NO on success.
 */
t_error	history_load_size_env(t_history *state);

#endif
