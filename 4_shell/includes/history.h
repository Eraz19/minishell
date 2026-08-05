/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 19:08:26 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 19:08:27 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# include "history_file.h"
# include "history_adapter.h"

/**
 * @defgroup history History API
 * @brief Interactive command history.
 *
 * The history module records every command line the interactive reader
 * consumes: text accumulates across PS1/PS2 reads into a pending entry,
 * is committed to the in-memory list at the next prompt, mirrored into
 * readline for arrow-key recall, and persisted to the history file
 * (@c HISTFILE, else @c HOME/.sh_history) when the shell exits. File
 * I/O failures only disable persistence (diagnostic printed): the
 * module never alters the shell control flow. Its whole error surface
 * is @c ERR_NO plus allocation @c ERR_LIBC — see the audit above
 * @ref requalify_history_error (history_error.c).
 */

/* ************************************************************************* */
/*                                  TYPES                                    */
/* ************************************************************************* */

/**
 * @ingroup history
 * @struct s_history
 * @brief Aggregated state of the command history module.
 *
 * @var s_history::err Last error recorded by a history operation.
 * @var s_history::file Persistent file state (pathname, staged bytes,
 *                      loaded count), managed by the history_file
 *                      submodule.
 * @var s_history::list In-memory committed entries, managed by the
 *                      history_list submodule.
 * @var s_history::adapter readline mirror bookkeeping, managed by the
 *                         history_adapter submodule.
 * @var s_history::current_input Command accumulated across PS1/PS2
 *                               reads until committed by
 *                               @ref history_save_entry (owned).
 */
typedef struct s_history
{
	t_error				err;
	t_history_file		file;
	t_history_list		list;
	t_history_adapter	adapter;
	t_string			current_input;
}	t_history;

/* ************************************************************************* */
/*                                LIFE_CYCLE                                 */
/* ************************************************************************* */

/**
 * @ingroup history
 * @brief Zeroes @p state and initializes every submodule state.
 *
 * @param state History state; initialized by the function (borrowed).
 */
void	history_init(t_history *state);

/**
 * @ingroup history
 * @brief Loads the module: resolves the history file pathname
 *        (@c HISTFILE, else @c HOME/.sh_history), reads @c HISTSIZE,
 *        moves the newest entries of the file into the list and mirrors
 *        them into readline.
 *
 * @note Missing pathname, unopenable file or malformed entries disable
 *       persistent history with a diagnostic and still report @c ERR_NO.
 *
 * @param state Already initialized history state (borrowed).
 * @return @c ERR_NO on success or absorbed lane. Module-produced
 *         failures: @c ERR_LIBC (failed allocation building the default
 *         pathname or pushing an entry). Module-external errors (env,
 *         serializer — allocation @c ERR_LIBC today) bubble through
 *         unlisted; see the audit in @c history_error.c.
 */
t_error	history_load(t_history *state);

/**
 * @ingroup history
 * @brief Releases the list, the file state and the pending input, and
 *        clears the readline history.
 *
 * @param state Already initialized history state (borrowed).
 */
void	history_free(t_history *state);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup history
 * @brief Appends @p entry to the command being accumulated by the shell
 *        instance's history.
 *
 * @param entry Text read at the prompt, appended verbatim including its
 *              trailing newline (borrowed, read-only).
 * @return @c ERR_NO on success, @c ERR_LIBC on allocation failure.
 */
t_error	history_append_to_entry(t_string *entry);

/**
 * @ingroup history
 * @brief Appends the list entries newer than the loaded count, then the
 *        pending input, to the history file (created @c 0600 when
 *        missing); operates on the shell instance's history.
 *
 * @note Unopenable or unwritable file: diagnostic printed, persistent
 *       history disabled, @c ERR_NO reported.
 *
 * @return @c ERR_NO on success or absorbed lane. Module-produced
 *         failures: @c ERR_LIBC (failed allocation staging the
 *         serialized content). Module-external errors (serializer —
 *         allocation @c ERR_LIBC today) bubble through unlisted; see
 *         the audit in @c history_error.c.
 */
t_error	history_save(void);

/**
 * @ingroup history
 * @brief Commits the accumulated input of the shell instance's history
 *        as one entry: strips its trailing newline, pushes it to the
 *        list and mirrors it into readline; an empty input is a no-op.
 *
 * @note The pending input's storage moves into the list; the pending
 *       input is reset to empty.
 *
 * @return @c ERR_NO on success, @c ERR_LIBC on allocation failure.
 */
t_error	history_save_entry(void);

#endif
