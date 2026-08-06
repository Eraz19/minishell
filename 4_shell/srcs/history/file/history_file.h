/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_file.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:08:38 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 17:28:40 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_FILE_H
# define HISTORY_FILE_H

# include "libft.h"
# include "error.h"
# include "history_list.h"

/* ************************************************************************* */
/*                                  TYPES                                    */
/* ************************************************************************* */

/**
 * @ingroup history
 * @struct s_history_file
 * @brief Persistent storage lane of the history module.
 *
 * @var s_history_file::err Last error recorded by a file operation.
 * @var s_history_file::path History file pathname; empty when persistent
 *                           history is disabled (owned).
 * @var s_history_file::content Staging area: raw file bytes during load,
 *                              serialized new entries during save; freed
 *                              after each use (owned).
 * @var s_history_file::loaded_count Number of entries moved into the
 *                                   list at load time; the save lane
 *                                   appends list entries from this
 *                                   index.
 */
typedef struct s_history_file
{
	t_error		err;
	t_string	path;
	t_string	content;
	size_t		loaded_count;
}	t_history_file;

/* ************************************************************************* */
/*                                LIFE_CYCLE                                 */
/* ************************************************************************* */

/**
 * @ingroup history
 * @brief Zeroes the state and initializes @c path and @c content.
 *
 * @param history_file File state; initialized by the function (borrowed).
 */
void	history_file_init(t_history_file *history_file);

/**
 * @ingroup history
 * @brief Reads the history file, deserializes its entries and moves the
 *        newest @p max of them into @p history_list; records the loaded
 *        count and frees the staging content.
 *
 * @note Empty pathname, unopenable file or malformed lines: diagnostic
 *       printed where relevant, the lane absorbed or the line skipped,
 *       and the load continues without persistent entries.
 *
 * @param history_file File state with @c path already resolved, possibly
 *                     empty (borrowed).
 * @param history_list Already initialized destination list (borrowed).
 * @param max Maximum number of entries to move; negative moves all of
 *            them.
 * @return @c ERR_NO on success or absorbed lane. Module-produced
 *         failures: @c ERR_LIBC (failed entry push). Module-external
 *         errors (serializer — allocation @c ERR_LIBC today) bubble
 *         through unlisted; see the audit in @c history_error.c.
 */
t_error	history_file_load(
			t_history_file *history_file,
			t_history_list *history_list,
			ssize_t max);

/**
 * @ingroup history
 * @brief Releases @c path and @c content and resets the loaded count.
 *
 * @param history_file Already initialized file state (borrowed).
 */
void	history_file_free(t_history_file *history_file);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup history
 * @brief Appends the staged @c content to the history file
 *        (@c O_CREAT | @c O_WRONLY | @c O_APPEND, mode @c 0600); no-op
 *        when @c path or @c content is empty.
 *
 * @param history_file File state with staged content (borrowed).
 * @return @c ERR_NO: open, write and close failures are printed then
 *         absorbed (persistent history disabled) — see the audit in
 *         @c history_error.c.
 */
t_error	write_history_file(t_history_file *history_file);

#endif
