/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:11:40 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 16:27:11 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "lexer.h"

/** @defgroup heredoc Here-document
 *  @brief String-based POSIX 2.7.4 here-document capture (no temporary
 *         files): the body is consumed from the live lexer input at parse
 *         time and kept as a string for later expansion.
 *
 *  The delimiter is matched on physical lines, each compared whole
 *  (documented deviation: bash and dash join @c \\<newline> continuations
 *  at read time instead). A missing delimiter surfaces as the printed
 *  @c ERR_NO_DELIM (converted from the end-of-input report at
 *  production, see @ref error_missing_delimiter) with the body holding
 *  everything read until end of input; the scanner endpoint absorbs it
 *  to @c ERR_NO — the here-document is treated as terminated by the end
 *  of input, POSIX 2.7.4 "should, but need not, be a redirection error"
 *  (documented benign choice, diagnostic still printed).
 */

/* ************************************************************************* */
/*                                  TYPES                                    */
/* ************************************************************************* */

/**
 * @ingroup heredoc
 * @enum e_here_mode
 * @brief Body treatment selected by the redirection operator.
 *
 * @var e_here_mode::HEREDOC_MODE_NORMAL
 *      @c <<: body kept as read.
 * @var e_here_mode::HEREDOC_MODE_TAB_STRIP
 *      @c <<-: leading tabs stripped from body and delimiter lines
 *      (POSIX 2.7.4).
 */
typedef enum e_here_mode
{
	HEREDOC_MODE_NORMAL,
	HEREDOC_MODE_TAB_STRIP
}	t_here_mode;

/* ************************************************************************* */
/*                                   OPS                                     */
/* ************************************************************************* */

/**
 * @ingroup heredoc
 * @brief Reads the here-document body: consumes physical lines from a
 *        private copy of the current lexer input (reading PS2
 *        continuations when it runs out) until the line matching the
 *        expanded @p delim, then advances the real input cursor past the
 *        consumed body.
 *
 * @note The body is kept raw: no expansion or escape processing happens
 *       here (the expander re-lexes it later with @c EXP_HEREDOC when the
 *       delimiter was unquoted). The delimiter line itself is consumed but
 *       not part of the body.
 *
 * @param lexer Already initialized lexer whose current input cursor is
 *              advanced past the body on success and on the
 *              missing-delimiter lane (borrowed).
 * @param out Receives the body; initialized by the function on success
 *            and on the missing-delimiter lane (body = everything read
 *            until end of input), untouched on other failures (borrowed).
 * @param delim Delimiter word token, expanded with quote removal to build
 *              the match text (borrowed, read-only).
 * @param strip True for @c <<-: leading tabs stripped from body and
 *              delimiter lines.
 * @return @c ERR_NO on success; @c ERR_NO_DELIM (printed, missing
 *         delimiter — absorbed to @c ERR_NO by the scanner endpoint,
 *         @p out still delivered) or @c ERR_LIBC (module allocation
 *         failure) on module-produced failure. Module-external errors
 *         (delimiter expansion by the expander, params, sig on the PS2
 *         read) bubble through unlisted.
 */
t_error	heredoc_read_body(
			t_lexer *lexer,
			t_string *out,
			t_token *delim,
			bool strip);

/**
 * @ingroup heredoc
 * @brief Re-lexes an unquoted-delimiter body with the here-document rules
 *        (POSIX 2.7.4: @c \\ behaves as inside double-quotes, expansions
 *        recognized, no quoting constructs) on a throwaway shell instance,
 *        extracting the construct spans and embedded command-substitution
 *        ASTs, prefixed with a @c CONTEXT_HEREDOC item covering the whole
 *        body.
 *
 * @param stack_out Receives the context spans; initialized by the function
 *                  (borrowed).
 * @param vec_out Receives the embedded ASTs; initialized by the function
 *                (borrowed).
 * @param body In/out: the raw body text going in, replaced by the scanned
 *             value (escaped newlines removed) on success; must be
 *             initialized by the caller, left empty on failure — except
 *             when pushing the text into the lexer fails, where the
 *             caller keeps it (borrowed).
 * @return @c ERR_NO on success; @c ERR_LIBC, @c ERR_POSIX_SYNTAX
 *         (printed) or @c ERR_VEOF on module-produced failure.
 *         Module-external errors (throwaway shell instance, embedded
 *         command-substitution parse) bubble through unlisted.
 */
t_error	heredoc_lex_body(t_context_stack *stack_out, t_ast_vector *vec_out,
			t_string *body);

#endif
