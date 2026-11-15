/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_recognition_context_scan.h                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:12:37 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 16:51:46 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_RECOGNITION_CONTEXT_SCAN_H
# define TOKEN_RECOGNITION_CONTEXT_SCAN_H

# include "token_recognition_context.h"

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup lexer
 * @brief Generic construct scanner: consumes the opening delimiter, then
 *        applies the @p args hooks (end, escape, nested quoting, nested
 *        expansion, plain character) until the construct closes or an
 *        error stops the scan.
 *
 * @param args Rule set of the construct being scanned; built by the
 *             matching @c *_context_rules function.
 * @return @c ERR_NO on success; @c ERR_LIBC (allocation failure),
 *         @c ERR_POSIX_SYNTAX (printed, construct unterminated) or
 *         @c ERR_VEOF (end of input reported by the PS2 continuation
 *         request) on module-produced failure. Module-external errors
 *         (embedded command-substitution parse, params, sig) bubble
 *         through unlisted.
 */
t_error	scan_context(t_token_recognition_context args);

/**
 * @ingroup lexer
 * @brief Closes the construct: records the end of its span in the context
 *        item (skipped when the rule set carries none) and consumes the
 *        closing delimiter.
 *
 * @param args Rule set of the construct being scanned.
 * @return @c ERR_NO on success, @c ERR_LIBC if growing the token value
 *         fails.
 */
t_error	scan_context_end(t_token_recognition_context args);

/**
 * @ingroup lexer
 * @brief Applies the construct escape rules to the @c \\ at the cursor:
 *        when the construct allows line continuation, drops the escaped
 *        newline and returns to the scan loop; otherwise consumes the
 *        @c \\ and, when whitelisted, the escaped character.
 *
 * @note A @c \\ that is the last character of the input stays literal: the
 *       @c \\0 after it is never consumed, so the caller's next dispatch
 *       handles end-of-input (alias pop, PS2 continuation or plain EOF),
 *       per POSIX 2.2.1.
 *
 * @param args Escape rules of the construct being scanned.
 * @return @c ERR_NO on success, @c ERR_LIBC on allocation failure; at end
 *         of input the continuation set of @ref on_context_scan_eoi (see
 *         @ref scan_context for the full list).
 */
t_error	scan_context_escape(t_token_recognition_escape args);

/**
 * @ingroup lexer
 * @brief Opens the construct: marks the token as a word, records the start
 *        of the construct span (skipped when the rule set carries none)
 *        and consumes the opening delimiter.
 *
 * @param args Rule set of the construct being scanned.
 * @return @c ERR_NO on success, @c ERR_LIBC if growing the token value
 *         fails.
 */
t_error	scan_context_start(t_token_recognition_context args);

/**
 * @ingroup lexer
 * @brief Applies the construct rules to the plain character at the cursor:
 *        runs the end-of-input continuation on @c \\0 , the special
 *        handler when the construct defines one, or consumes the character
 *        verbatim.
 *
 * @param args Unescaped-character rules of the construct being scanned.
 * @return @c ERR_NO on success, @c ERR_LIBC on allocation failure; at end
 *         of input the continuation set of @ref on_context_scan_eoi (see
 *         @ref scan_context for the full list).
 */
t_error	scan_context_unescape(t_token_recognition_unescape args);

#endif
