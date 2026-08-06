/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_recognition.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:14:07 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 16:14:08 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_RECOGNITION_H
# define TOKEN_RECOGNITION_H

# include "lexer.h"

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup lexer
 * @brief Runs the POSIX token recognition rules on the current input until
 *        one token is delimited into @p token.
 *
 * @note In @c SCAN_MODE_CMD_SUB the very first emitted token is the
 *       @c TOKEN_DOLPAREN opener.
 *
 * @param lexer Already initialized lexer with a bound input (borrowed).
 * @param token Receives the token; initialized by the function. The caller
 *              releases it with @ref token_free (borrowed).
 * @return @c ERR_NO on success. Module-produced failures: @c ERR_LIBC
 *         (failed allocation or libc call), @c ERR_POSIX_SYNTAX (printed,
 *         construct left open — or trailing line continuation — when no
 *         more input is possible in any mode) and @c ERR_VEOF (end of
 *         input reported by the PS2 continuation request).
 *         Module-external errors (embedded command-substitution parse,
 *         params, sig) bubble through unlisted.
 */
t_error	recognize_token(t_lexer *lexer, t_token *token);

/**
 * @ingroup lexer
 * @brief Expansion rule: scans the expansion construct opening at the
 *        cursor into the current word token; @c $(( openings that turn out
 *        not to close as arithmetic are rescanned as command substitution.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @param context Expansion construct to scan (@c CONTEXT_PARAM,
 *                @c CONTEXT_CMD_SUB, @c CONTEXT_ARITH or
 *                @c CONTEXT_BACKTICK).
 * @return @c ERR_NO on success; @c ERR_LIBC, @c ERR_POSIX_SYNTAX
 *         (printed) or @c ERR_VEOF on module-produced failure (see
 *         @ref recognize_token for the failure conditions); the
 *         @c CONTEXT_ARITH rescan absorbs @c ERR_CTX_END_NOT_FOUND
 *         internally. Module-external errors bubble through unlisted.
 */
t_error	recognize_token_expansion_context(t_lexer *lexer, t_context context);

#endif
