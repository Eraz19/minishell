/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_name_expansion_.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:45:41 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 17:45:42 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_NAME_EXPANSION__H
# define PATH_NAME_EXPANSION__H

# include "expander_.h"

/** @defgroup expander_path_name_expansion Expander pathname expansion
 *  @brief POSIX pathname expansion (globbing) stage of the pipeline.
 *
 *  Per field: the word is quote-removed into a cleaned copy, split on
 *  @c / into path components (see @ref expander_path_comps), then
 *  globbed against the filesystem (see @ref expander_globbing). A field
 *  with matches is replaced by one field per matched path; a field
 *  without any special component, or without matches, passes through
 *  unchanged.
 */

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup expander_path_name_expansion
 * @brief Applies pathname expansion to every field: consumes
 *        @c expander->fields and rebuilds it with, per field, either
 *        the sorted matched paths (one field per path, items tagged
 *        @c is_expand_res) or the original field untouched.
 *
 * @note A no-op when the @c noglob shell option is active.
 * @warning On failure the fields produced so far are freed and
 *          @c expander->fields is left partially consumed.
 * @param expander Loaded expander state (borrowed).
 * @return @c ERR_SHELL_NOT_FOUND if the shell parameters are
 *         unavailable; @c ERR_EMPTY_STACK or @c ERR_INDEX_OUT_OF_BOUND
 *         on a field or word read inconsistency; @c ERR_LIBC on
 *         allocation failure; @c ERR_NO on success.
 */
t_error	path_name_expansion(t_expander *expander);

#endif
