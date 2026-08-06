/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_body_priv.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:11:27 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 16:11:28 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_BODY_PRIV_H
# define HEREDOC_BODY_PRIV_H

# include "heredoc_body.h"

/* ************************************************************************* */
/*                                  DELIM                                    */
/* ************************************************************************* */

/**
 * @ingroup heredoc
 * @brief Builds the delimiter match text: expands @p delim with quote
 *        removal, then appends a newline so it compares equal to a whole
 *        physical line.
 *
 * @param out Receives the match text; initialized by the function, freed
 *            by the function on failure (borrowed).
 * @param delim Delimiter word token (borrowed, read-only).
 * @return @c ERR_NO on success; @c ERR_LIBC (module allocation failure)
 *         on module-produced failure. Module-external errors (delimiter
 *         expansion by the expander) bubble through unlisted.
 */
t_error	build_heredoc_delimiter(t_string *out, t_token *delim);

/* ************************************************************************* */
/*                                 ERROR                                     */
/* ************************************************************************* */

/**
 * @ingroup heredoc
 * @brief Prints the missing-delimiter diagnostic naming the expected
 *        delimiter and requalifies the end-of-input report into the
 *        printed @c ERR_NO_DELIM — the production-site conversion that
 *        keeps @c ERR_VEOF out of the scanner error frontier.
 *
 * @note The returned error is also mirrored into @c body->err, so the
 *       caller may propagate either. It leaves with @c printed set:
 *       every later @ref error_print on it is a guarded no-op, and the
 *       scanner endpoint absorbs @c ERR_NO_DELIM to @c ERR_NO (benign
 *       missing-delimiter choice, POSIX 2.7.4).
 *
 * @warning Truncates the trailing newline of @c body->delim in place to
 *          display the bare delimiter: @p body's match text is unusable
 *          afterwards — call only on the terminal no-more-input lane.
 *
 * @param body Body state whose delimiter names the diagnostic; its
 *             @c delim text is truncated and its @c err overwritten
 *             (borrowed).
 * @return The printed @c ERR_NO_DELIM, always.
 */
t_error	error_missing_delimiter(t_body *body);

#endif
