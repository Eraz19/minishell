/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing_.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:45:05 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 17:45:06 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBBING__H
# define GLOBBING__H

# include "expander_.h"
# include "path_comps_.h"

/** @defgroup expander_globbing Expander globbing
 *  @brief Candidate-path walk matching the loaded path components
 *         against the filesystem.
 */

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup expander_globbing
 * @brief Globs one quote-removed word given as its loaded components:
 *        when at least one component is special, walks the filesystem
 *        (special components match directory entries, literal ones are
 *        appended without a lookup) and pushes every matched path onto
 *        @c expander->fields_exp as its own field, sorted bytewise,
 *        items tagged @c is_expand_res.
 *
 * @note A candidate directory that cannot be opened yields no matches
 *       and no error. When the last component is literal, only
 *       candidates @c lstat can reach are kept.
 * @param expander Expander state receiving the matched fields
 *                 (borrowed).
 * @param src Loaded components, released by the function in every
 *            outcome and left re-initialized empty, so a redundant
 *            @ref path_comps_free by the caller stays safe (borrowed).
 * @param globbed Set to true only when at least one matched field was
 *                emitted: the caller must then drop the original word
 *                (borrowed).
 * @return @c ERR_LIBC on allocation failure, @c ERR_NO on success
 *         (zero matches included; container read inconsistencies are
 *         caught by assertion).
 */
t_error	path_globbing(t_expander *expander, t_path_comps *src, bool *globbed);

#endif
