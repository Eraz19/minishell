/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal_context_.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 17:45:59 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 18:38:55 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTE_REMOVAL_CONTEXT__H
# define QUOTE_REMOVAL_CONTEXT__H

# include "expander_.h"

/** @defgroup expander_quote_removal_context Quote removal contexts
 *  @brief Per-quoting-context scans of quote removal: each one forwards
 *         the content of its span and drops the marks and effective
 *         escapes that POSIX 2.6.7 removes.
 *
 *  @note The dispatcher (@ref quote_remove_char) has already consumed
 *        the opening mark when a scan starts. Every function also
 *        records its result in @c expander->err before returning it.
 */

/**
 * @ingroup expander_quote_removal_context
 * @struct s_context_args
 * @brief Rules of one quoting-context scan (see @ref context_scan).
 *
 * @var s_context_args::word Input word, consumed from the front
 *                           (borrowed).
 * @var s_context_args::word_expanded Destination word receiving the kept
 *                                    items (borrowed).
 * @var s_context_args::is_end Tells whether a character closes the
 *                             context; matches the lexer @c is_end
 *                             signature and is called with @c NULL as
 *                             second argument. @c NULL means the scan
 *                             only ends with the word
 *                             (borrowed, read-only).
 * @var s_context_args::is_in_whitelist Tells whether a backslash escapes
 *                                      the character in this context;
 *                                      @c NULL disables escape handling
 *                                      (borrowed, read-only).
 */
typedef struct s_context_args
{
	t_word		*word;
	t_word		*word_expanded;
	bool		(*is_end)(char _, void *);
	bool		(*is_in_whitelist)(char);
}	t_context_args;

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup expander_quote_removal_context
 * @brief Scans an ANSI-C quoted span (@c $'...') until the closing
 *        @c '\'': every backslash is dropped and the character it
 *        escapes forwarded (the whitelist accepts everything).
 *
 * @warning The caller must have consumed both the @c $ and the opening
 *          @c '\'' (see @ref quote_remove_char).
 * @param expander Expander state whose @c word is scanned into
 *                 @c word_exp (borrowed).
 * @note A missing closing quote is a lexer-guarantee violation, caught
 *       by assertion.
 * @return @c ERR_LIBC if a push fails, @c ERR_NO on success.
 */
t_error	context_dollar_squote(t_expander *expander);

/**
 * @ingroup expander_quote_removal_context
 * @brief Scans a double-quoted span until the closing @c '"': a
 *        backslash is dropped before @c $, @c `, @c \ or @c " and kept
 *        literal before anything else.
 *
 * @param expander Expander state whose @c word is scanned into
 *                 @c word_exp (borrowed).
 * @note A missing closing quote or a dangling backslash is a
 *       lexer-guarantee violation, caught by assertion.
 * @return @c ERR_LIBC if a push fails, @c ERR_NO on success.
 */
t_error	context_dquote(t_expander *expander);

/**
 * @ingroup expander_quote_removal_context
 * @brief Handles one here-document item (no marks, no end detector):
 *        forwards @p item, except that a backslash escaping @c $, @c `
 *        or @c \ is dropped and the escaped item forwarded (before any
 *        other character both are kept).
 *
 * @note A backslash that ends the word is forwarded literally, unlike
 *       the unquoted case (see @ref quote_remove_char).
 * @param expander Expander state whose @c word may provide the escaped
 *                 item (borrowed).
 * @param item Already popped item to forward (copied by value).
 * @return @c ERR_LIBC if a push fails, @c ERR_NO on success.
 */
t_error	context_heredoc(t_expander *expander, t_word_item item);

/**
 * @ingroup expander_quote_removal_context
 * @brief Generic scan driver: pops items of @c args.word and forwards
 *        them to @c args.word_expanded until @c args.is_end matches; the
 *        closing item is dropped. Expansion-result items are always
 *        forwarded verbatim (they never end the scan nor escape). A
 *        non-result backslash, when @c args.is_in_whitelist is set,
 *        is dropped if the next character is whitelisted and kept
 *        otherwise; the escaped item is forwarded either way.
 *
 * @param expander Expander state recording the error (borrowed).
 * @param args Scan rules (copied by value; its pointers stay borrowed).
 * @note A word ending before @c args.is_end matches (or on a dangling
 *       backslash) is a lexer-guarantee violation, caught by assertion.
 * @return @c ERR_LIBC if a push fails, @c ERR_NO on success.
 */
t_error	context_scan(t_expander *expander, t_context_args args);

/**
 * @ingroup expander_quote_removal_context
 * @brief Scans a single-quoted span until the closing @c '\'': no
 *        escapes, every character is forwarded literally.
 *
 * @param expander Expander state whose @c word is scanned into
 *                 @c word_exp (borrowed).
 * @note A missing closing quote is a lexer-guarantee violation, caught
 *       by assertion.
 * @return @c ERR_LIBC if a push fails, @c ERR_NO on success.
 */
t_error	context_squote(t_expander *expander);

#endif
