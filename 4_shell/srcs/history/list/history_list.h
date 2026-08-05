/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_list.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:08:56 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 17:33:19 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_LIST_H
# define HISTORY_LIST_H

# include "error.h"
# include "libft.h"

/* ************************************************************************* */
/*                                  TYPES                                    */
/* ************************************************************************* */

/**
 * @ingroup history
 * @typedef t_history_list
 * @brief List of committed history entries, backed by a @ref t_vector of
 *        @ref t_string values (owned by the list).
 */
typedef t_vector	t_history_list;

/* ************************************************************************* */
/*                                LIFE_CYCLE                                 */
/* ************************************************************************* */

/**
 * @ingroup history
 * @brief Initializes @p list as an empty entry list.
 *
 * @param list List to initialize; initialized by the function (borrowed).
 */
void	history_list_init(t_history_list *list);

/**
 * @ingroup history
 * @brief Moves the entries of @p entries from index @p start to the end
 *        into @p history_list: each moved string's storage is taken and
 *        its source slot marked borrowed, so freeing @p entries
 *        afterwards cannot double-free.
 *
 * @param history_list Already initialized destination list (borrowed).
 * @param entries Source entries; moved slots are emptied (borrowed).
 * @param start First index to move; a @p start past the end is a no-op.
 * @return @c ERR_NO on success, including when nothing is moved;
 *         @c ERR_LIBC on push failure.
 */
t_error	history_list_load(
			t_history_list *history_list,
			t_vector *entries,
			size_t start);

/**
 * @ingroup history
 * @brief Releases every entry and the list storage.
 *
 * @param list Already initialized list (borrowed).
 */
void	history_list_free(t_history_list *list);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup history
 * @brief Points @p item at entry @p i of @p list.
 *
 * @warning @c i must be below @c list->len (asserted).
 * @warning The returned pointer aims into the list storage: any push may
 *          move it, so it must be re-fetched after every mutation and
 *          never freed through @p item.
 *
 * @param list Already initialized, non-empty list (borrowed).
 * @param item Receives the address of the stored entry (borrowed).
 * @param i Entry index.
 */
void	history_list_get(t_history_list *list, const t_string **item, size_t i);

/**
 * @ingroup history
 * @brief Appends @p item to @p list by shallow copy.
 *
 * @warning On failure the entry is not stored and the caller keeps
 *          ownership of @p item's storage.
 *
 * @param list Already initialized list (borrowed).
 * @param item Entry to append; its storage now belongs to the list, the
 *             caller must re-initialize it instead of freeing it
 *             (ownership taken by the list).
 * @return @c ERR_NO on success, @c ERR_LIBC on allocation failure.
 */
t_error	history_list_push(t_history_list *list, const t_string *item);

#endif
