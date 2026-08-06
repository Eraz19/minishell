/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:43:19 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/05 23:02:39 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION__H
# define EXPANSION__H

# include "expander.h"
# include "field_.h"

/* ************************************************************************* */
/*                                LIFE_CYCLE                                 */
/* ************************************************************************* */

/**
 * @ingroup expander_priv
 * @brief Initializes @p expansion as an empty field list.
 *
 * @param expansion Expansion initialized by the function (borrowed).
 */
void	expansion_init(t_expansion *expansion);

/**
 * @ingroup expander_priv
 * @brief Converts the fields of @p src into strings and loads them into
 *        @p out, consuming @p src as it goes; @p out is freed and
 *        re-emptied on failure.
 *
 * @param out Expansion initialized by the function (borrowed).
 * @param src Already initialized fields to consume; fields not yet
 *            converted are left inside on failure (borrowed).
 * @return @c ERR_LIBC on allocation failure; @c ERR_NO on success
 *         (internal inconsistencies are caught by assertion).
 */
t_error	expansion_load(t_expansion *out, t_fields *src);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup expander_priv
 * @brief Moves the last field of @p expansion into @p out.
 *
 * @warning @p expansion must not be empty (asserted).
 * @param out Receives the field; the caller owns it and releases it
 *            with @c string_free (borrowed).
 * @param expansion Already initialized, non-empty expansion (borrowed).
 */
void	expansion_bpop(t_string *out, t_expansion *expansion);

/**
 * @ingroup expander_priv
 * @brief Moves the first field of @p expansion into @p out.
 *
 * @warning @p expansion must not be empty (asserted).
 * @param out Receives the field; the caller owns it and releases it
 *            with @c string_free (borrowed).
 * @param expansion Already initialized, non-empty expansion (borrowed).
 */
void	expansion_fpop(t_string *out, t_expansion *expansion);

/**
 * @ingroup expander_priv
 * @brief Appends @p str to @p expansion by shallow copy.
 *
 * @warning On failure the field is not stored and the caller keeps
 *          ownership of @p str's storage.
 *
 * @param expansion Already initialized expansion (borrowed).
 * @param str Field to append; the caller must re-initialize it instead
 *            of freeing it (ownership taken by @p expansion).
 * @return @c ERR_LIBC on allocation failure, @c ERR_NO on success.
 */
t_error	expansion_push(t_expansion *expansion, t_string *str);

#endif
