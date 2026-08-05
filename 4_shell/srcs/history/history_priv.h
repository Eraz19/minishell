/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_priv.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:09:28 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/05 19:00:03 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_PRIV_H
# define HISTORY_PRIV_H

# include "error.h"
# include "history.h"

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup history
 * @brief Stages into @c history->file.content the serialized list
 *        entries from index @p start to the end, then the pending
 *        input; the staged content is freed on failure.
 *
 * @param history Already initialized history state (borrowed).
 * @param start First list index to stage; the save lane passes the
 *              loaded count so only this session's entries are
 *              appended.
 * @return @c ERR_NO on success, @c ERR_LIBC on serialize or append
 *         allocation failure.
 */
t_error	build_saving_file_content(t_history *history, size_t start);

/* ************************************************************************* */
/*                                 ERROR                                     */
/* ************************************************************************* */

/**
 * @ingroup history
 * @brief Boundary mapping of raw internal errors to the module's public
 *        error surface — the identity, final: @c ERR_NO and @c ERR_LIBC
 *        both belong to the allowed pass-through set; the full bubble-up
 *        audit lives above the implementation (history_error.c).
 *
 * @param err Raw error to requalify.
 * @return @p err unchanged.
 */
t_error	requalify_history_error(t_error err);

#endif
