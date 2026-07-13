#ifndef HISTORY_FILE__H
# define HISTORY_FILE__H

# include "error.h"
# include "history_list_.h"

/** @defgroup history_file History file backing
 *  @brief Persistent, serialized storage of the history entries.
 *
 *  Every open, read or write failure is printed with the file path as a
 *  @c persistent @c history @c disabled warning and degraded to
 *  @c ERR_NO, so a broken history file never aborts the shell.
 *  @c ERR_INTERRUPTED is never degraded.
 */

/**
 * @ingroup history_file
 * @struct s_history_file
 * @brief On-disk backing of the history.
 *
 * @var s_history_file::err Last error recorded by the file backing.
 * @var s_history_file::path Path of the history file, a @ref t_string
 *                           owned by the backing; empty when persistence
 *                           is disabled.
 * @var s_history_file::content Working text holding serialized entries, a
 *                              @ref t_string owned by the backing;
 *                              consumed while parsing and rebuilt before
 *                              writing.
 * @var s_history_file::loaded_count Number of entries loaded from the
 *                                   file, marking the prefix already
 *                                   persisted.
 */
typedef struct s_history_file
{
	t_error		err;
	t_string 	path;
	t_string	content;
	size_t		loaded_count;
}	t_history_file;

/* ************************************************************************* */
/*                                LIFE_CYCLE                                 */
/* ************************************************************************* */

/**
 * @ingroup history_file
 * @brief Zeroes @p state and initializes its path and content strings.
 *
 * @param state File backing initialized by the function (borrowed).
 */
void	history_file_init(t_history_file *state);

/**
 * @ingroup history_file
 * @brief Reads and parses the history file into @p list.
 *
 * Reads the whole file, deserializes its entries in stored order
 * (malformed entries are skipped) and appends the last @p max entries to
 * @p list in chronological order (@p max < 0 means no limit). A missing,
 * unreadable or empty file leaves @p list unchanged and reports success.
 * The number of entries actually loaded is recorded in
 * @c state->loaded_count.
 *
 * @param state Already initialized file backing (borrowed).
 * @param list Destination entry list, already initialized by the caller;
 *             it takes ownership of each loaded entry (borrowed).
 * @param max Maximum number of entries to keep, negative for all.
 * @return @c ERR_LIBC on allocation failure or if closing the file fails;
 *         @c ERR_INTERRUPTED when a signal interrupts the close;
 *         @c ERR_NO on success or when persistence is disabled (printed
 *         warning).
 */
t_error	history_file_load(
			t_history_file *state,
			t_history_list *list,
			ssize_t max);

/**
 * @ingroup history_file
 * @brief Frees the path and content strings of @p state, then zeroes it.
 *
 * @param state Already initialized file backing (borrowed).
 */
void	history_file_free(t_history_file *state);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup history_file
 * @brief Reads the whole history file into the backing's content string
 *        (created if missing).
 *
 * Does nothing when the path is empty. Open and read failures are printed
 * with the path and degraded to @c ERR_NO.
 *
 * @warning A signal interrupting the read is degraded like a read
 *          failure: the read helper cannot distinguish them (see the
 *          history.h warning).
 * @param state Already initialized file backing (borrowed).
 * @return @c ERR_LIBC if closing the file fails; @c ERR_INTERRUPTED when
 *         a signal interrupts the close; @c ERR_NO on success or when
 *         persistence is disabled.
 */
t_error	history_file_read(t_history_file *state);

/**
 * @ingroup history_file
 * @brief Appends the backing's content string to the history file on
 *        disk.
 *
 * Does nothing when the path or the content is empty. Open and write
 * failures are printed with the path and degraded to @c ERR_NO.
 *
 * @param state Already initialized file backing (borrowed).
 * @return @c ERR_INTERRUPTED when a signal interrupts the write or the
 *         close (never degraded); @c ERR_LIBC if closing the file fails;
 *         @c ERR_NO on success or when persistence is disabled.
 */
t_error	history_file_write(t_history_file *state);

#endif
