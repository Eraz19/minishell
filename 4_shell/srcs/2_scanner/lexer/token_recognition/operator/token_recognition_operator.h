/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_recognition_operator.h                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:13:27 by adouieb           #+#    #+#             */
/*   Updated: 2026/08/04 16:13:28 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_RECOGNITION_OPERATOR_H
# define TOKEN_RECOGNITION_OPERATOR_H

# include "lexer.h"

/* ************************************************************************* */
/*                                PREDICATE                                  */
/* ************************************************************************* */

/**
 * @ingroup lexer
 * @brief Returns true when an operator token is under construction (any
 *        type other than @c TOKEN_NONE and @c TOKEN_TOKEN).
 *
 * @param lexer Already initialized lexer (borrowed, read-only).
 */
bool	is_inside_operator(t_lexer *lexer);

/**
 * @ingroup lexer
 * @brief Returns true when the character at the cursor starts a new
 *        operator while no operator is under construction.
 *
 * @param lexer Already initialized lexer (borrowed, read-only).
 */
bool	is_new_operator(t_lexer *lexer);

/**
 * @ingroup lexer
 * @brief Returns true when the character at the cursor can start or extend
 *        an operator, given the token under construction.
 *
 * @param lexer Already initialized lexer (borrowed, read-only).
 */
bool	is_operator_char(t_lexer *lexer);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup lexer
 * @brief Consumes the operator character at the cursor, dispatching to the
 *        per-character consume function to pick the operator token type.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @return @c ERR_NO on success, @c ERR_LIBC on allocation failure; a
 *         character fitting no operator from the current token state is
 *         asserted out (debug builds), not reported.
 */
t_error	token_recognition_consume_operator(t_lexer *lexer);

/* ************************************************************************* */
/*                                  PIPE                                     */
/* ************************************************************************* */

/**
 * @ingroup lexer
 * @brief Returns true when @c | fits the token under construction
 *        (@c TOKEN_PIPE, @c TOKEN_GREAT or no operator).
 *
 * @param lexer Already initialized lexer (borrowed, read-only).
 */
bool	is_char_pipe_fit_operator(t_lexer *lexer);

/**
 * @ingroup lexer
 * @brief Consumes @c | into @c TOKEN_OR_IF, @c TOKEN_CLOBBER or
 *        @c TOKEN_PIPE depending on the token under construction.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @return @c ERR_NO on success, @c ERR_LIBC on allocation failure; a
 *         token state fitting no @c | operator is asserted out (debug
 *         builds), not reported.
 */
t_error	token_recognition_consume_pipe(t_lexer *lexer);

/* ************************************************************************* */
/*                                  LESS                                     */
/* ************************************************************************* */

/**
 * @ingroup lexer
 * @brief Returns true when @c < fits the token under construction
 *        (@c TOKEN_LESS or no operator).
 *
 * @param lexer Already initialized lexer (borrowed, read-only).
 */
bool	is_char_less_fit_operator(t_lexer *lexer);

/**
 * @ingroup lexer
 * @brief Consumes @c < into @c TOKEN_DLESS or @c TOKEN_LESS depending on
 *        the token under construction.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @return @c ERR_NO on success, @c ERR_LIBC on allocation failure; a
 *         token state fitting no @c < operator is asserted out (debug
 *         builds), not reported.
 */
t_error	token_recognition_consume_less(t_lexer *lexer);

/* ************************************************************************* */
/*                                 GREAT                                     */
/* ************************************************************************* */

/**
 * @ingroup lexer
 * @brief Returns true when @c > fits the token under construction
 *        (@c TOKEN_LESS, @c TOKEN_GREAT or no operator).
 *
 * @param lexer Already initialized lexer (borrowed, read-only).
 */
bool	is_char_great_fit_operator(t_lexer *lexer);

/**
 * @ingroup lexer
 * @brief Consumes @c > into @c TOKEN_LESSGREAT, @c TOKEN_DGREAT or
 *        @c TOKEN_GREAT depending on the token under construction.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @return @c ERR_NO on success, @c ERR_LIBC on allocation failure; a
 *         token state fitting no @c > operator is asserted out (debug
 *         builds), not reported.
 */
t_error	token_recognition_consume_great(t_lexer *lexer);

/* ************************************************************************* */
/*                              SEMICOLON                                    */
/* ************************************************************************* */

/**
 * @ingroup lexer
 * @brief Returns true when @c ; fits the token under construction
 *        (@c TOKEN_SCOLON or no operator).
 *
 * @param lexer Already initialized lexer (borrowed, read-only).
 */
bool	is_char_semicolon_fit_operator(t_lexer *lexer);

/**
 * @ingroup lexer
 * @brief Consumes @c ; into @c TOKEN_DSEMI or @c TOKEN_SCOLON depending on
 *        the token under construction.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @return @c ERR_NO on success, @c ERR_LIBC on allocation failure; a
 *         token state fitting no @c ; operator is asserted out (debug
 *         builds), not reported.
 */
t_error	token_recognition_consume_semicolon(t_lexer *lexer);

/* ************************************************************************* */
/*                              AMPERSAND                                    */
/* ************************************************************************* */

/**
 * @ingroup lexer
 * @brief Returns true when @c & fits the token under construction
 *        (@c TOKEN_SCOLON, @c TOKEN_AMPERSAND, @c TOKEN_LESS,
 *        @c TOKEN_GREAT or no operator).
 *
 * @param lexer Already initialized lexer (borrowed, read-only).
 */
bool	is_char_ampersand_fit_operator(t_lexer *lexer);

/**
 * @ingroup lexer
 * @brief Consumes @c & into @c TOKEN_SEMI_AND, @c TOKEN_AND_IF,
 *        @c TOKEN_LESSAND, @c TOKEN_GREATAND or @c TOKEN_AMPERSAND
 *        depending on the token under construction.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @return @c ERR_NO on success, @c ERR_LIBC on allocation failure; a
 *         token state fitting no @c & operator is asserted out (debug
 *         builds), not reported.
 */
t_error	token_recognition_consume_ampersand(t_lexer *lexer);

#endif
