/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_file_priv.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:08:35 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/05 18:59:26 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_FILE_PRIV_H
# define HISTORY_FILE_PRIV_H

# include "history_file.h"

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup history
 * @brief Opens @p path with @p flags (mode @c 0600).
 *
 * @warning Open failures are absorbed after the diagnostic — check
 *          @c *out < 0, not the return value.
 *
 * @param out Receives the open file descriptor, or @c -1 on failure
 *            (borrowed).
 * @param path History file pathname (borrowed, read-only).
 * @param flags @c open(2) flag mask.
 * @return @c ERR_NO: open failures are printed then absorbed by
 *         @ref on_history_file_open_error.
 */
t_error	open_history_file(int *out, const char *path, int flags);

/**
 * @ingroup history
 * @brief Reads the whole history file into @c content (initialized by
 *        the function); no-op when @c path is empty.
 *
 * @param history_file Already initialized file state (borrowed).
 * @return @c ERR_NO: empty pathname, open and read failures are printed
 *         then absorbed (persistent history disabled) — see the audit
 *         in @c history_error.c.
 */
t_error	read_history_file(t_history_file *history_file);

/* ************************************************************************* */
/*                                   ERROR                                   */
/* ************************************************************************* */

/**
 * @ingroup history
 * @brief Prints the open diagnostic ("persistent history disabled") and
 *        absorbs the error.
 *
 * @param err Raw open error.
 * @param path Pathname for the diagnostic (borrowed, read-only).
 * @return @p err with its type forced to @c ERR_NO.
 */
t_error	on_history_file_open_error(t_error err, const char *path);

/**
 * @ingroup history
 * @brief Prints the read diagnostic ("persistent history disabled").
 *
 * @param err Raw read error.
 * @param path Pathname for the diagnostic (borrowed, read-only).
 * @return @p err unchanged.
 */
t_error	on_history_file_read_error(t_error err, const char *path);

/**
 * @ingroup history
 * @brief Prints the write diagnostic ("persistent history disabled") and
 *        absorbs the error.
 *
 * @param err Raw write or close error.
 * @param path Pathname for the diagnostic (borrowed, read-only).
 * @return @p err with its type forced to @c ERR_NO.
 */
t_error	on_history_file_write_error(t_error err, const char *path);

#endif
