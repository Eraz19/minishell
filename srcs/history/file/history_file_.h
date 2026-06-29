#ifndef HISTORY_FILE__H
# define HISTORY_FILE__H

# include "error.h"
# include "history_list_.h"

/**
 * @ingroup history
 * @struct s_history_file
 * @brief On-disk backing of the history.
 *
 * @var s_history_file::err Last error recorded by the file backing.
 * @var s_history_file::path Path of the history file (owned).
 * @var s_history_file::content Working buffer holding serialised entries,
 *                              consumed while parsing and rebuilt before
 *                              writing (owned).
 * @var s_history_file::loaded_count Number of entries loaded from the file,
 *                                   marking the prefix already persisted.
 */
typedef struct s_history_file
{
	t_error		err;
	t_string 	path;
	t_string	content;
	size_t		loaded_count;
}	t_history_file;

/**
 * @ingroup history
 * @brief Initialises a file backing to a zeroed value.
 *
 * @param state Pointer to the file backing to initialise (borrowed).
 */
void	history_file_init(t_history_file *state);

/**
 * @ingroup history
 * @brief Frees the path and content @ref t_string, then resets the file backing.
 *
 * Frees both the path and content @ref t_string, then resets the structure to
 * zero.
 *
 * @param state Pointer to the file backing to free (borrowed).
 */
void	history_file_free(t_history_file *state);

/**
 * @ingroup history
 * @brief Reads and parses the history file into @p list.
 *
 * Reads the whole file, deserialises its entries in stored order and appends
 * the last @p max entries to @p list while preserving chronological order
 * (@p max < 0 means no limit). If the file is missing, unreadable or empty,
 * leaves @p list unchanged and returns @c ERR_NO. The number of entries
 * actually loaded is recorded in state->loaded_count.
 *
 * @param state Pointer to the file backing (borrowed).
 * @param list Destination entry list, which takes ownership of each entry.
 * @param max Maximum number of entries to keep, or a negative value for all.
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	history_file_load(t_history_file *state, t_history_list *list, ssize_t max);

/**
 * @ingroup history
 * @brief Opens the history file, creating it when missing.
 *
 * Opens state->path with @p flags, retrying with O_CREAT if the file does
 * not exist.
 *
 * @param state Pointer to the file backing (borrowed).
 * @param fd Out-parameter receiving the opened descriptor.
 * @param flags open(2) flags to use.
 * @return ERR_NO on success, ERR_LIBC on failure.
 */
t_error	history_file_open(t_history_file *state, int *fd, int flags);

/**
 * @ingroup history
 * @brief Reads the whole history file into state->content.
 *
 * Leaves state->content empty when the file cannot be opened, cannot be
 * read or is empty. Open/read failures are downgraded to ERR_NO after a
 * warning so persistent history can be disabled without aborting the shell.
 *
 * @param state Pointer to the file backing (borrowed).
 * @return ERR_NO on success or when persistence is disabled.
 */
t_error	history_file_read(t_history_file *state);

/**
 * @ingroup history
 * @brief Appends state->content to the history file on disk.
 *
 * Does nothing when the path or the content buffer is empty. Open/write
 * failures are downgraded to ERR_NO after a warning so persistent history
 * can be disabled without aborting the shell.
 *
 * @param state Pointer to the file backing (borrowed).
 * @return ERR_NO on success or when persistence is disabled.
 */
t_error	history_file_write(t_history_file *state);

#endif
