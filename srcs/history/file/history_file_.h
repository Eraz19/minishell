/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_file_.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 16:00:20 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/12 14:32:26 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_FILE__H
# define HISTORY_FILE__H

# include "error.h"
# include "types.h"
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
	t_error	err;
	char 	*path;
	char	*content;
	size_t	loaded_count;
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
 * @brief Frees the content buffer and resets the file backing.
 *
 * @param state Pointer to the file backing to free (borrowed).
 */
void	history_file_free(t_history_file *state);

/**
 * @ingroup history
 * @brief Reads and parses the history file into @p list.
 *
 * Reads the whole file, then extracts entries from newest to oldest,
 * inserting each at the front of @p list so chronological order is preserved,
 * keeping at most @p max entries (@p max < 0 means no limit). Records the
 * resulting count in state->loaded_count.
 *
 * @param state Pointer to the file backing (borrowed).
 * @param list Destination entry list, which takes ownership of each entry.
 * @param max Maximum number of entries to keep, or a negative value for all.
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	history_file_load(t_history_file *state, t_history_list *list, ssize_t max);

/**
 * @ingroup history
 * @brief Extracts the last entry from the content buffer.
 *
 * Carves the trailing serialised entry out of state->content (mutating it)
 * and decodes it into a freshly allocated *entry owned by the caller. Sets
 * *entry to NULL when no entry remains; safe to call with NULL content.
 *
 * @param state Pointer to the file backing (borrowed).
 * @param entry Out-parameter receiving the decoded entry, or NULL when none
 *              remains.
 * @return ERR_NO on success or exhaustion, ERR_INCOHERENT_STATE on a
 *         malformed buffer, or ERR_LIBC on allocation failure.
 */
t_error	history_file_extract(t_history_file *state, char **entry);

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
 * Leaves state->content NULL when the file is empty.
 *
 * @param state Pointer to the file backing (borrowed).
 * @return ERR_NO on success, ERR_LIBC on failure.
 */
t_error	history_file_read(t_history_file *state);

/**
 * @ingroup history
 * @brief Appends state->content to the history file on disk.
 *
 * @param state Pointer to the file backing (borrowed).
 * @return ERR_NO on success, ERR_LIBC on failure.
 */
t_error	history_file_write(t_history_file *state);

#endif
