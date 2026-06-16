/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_operator_.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 10:06:15 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/10 16:51:54 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_OPERATOR__H
# define LEXER_OPERATOR__H

# include "lexer_.h"

/**
 * @ingroup scanner
 * @brief Tests whether the token being built is an operator in progress.
 * @param state Pointer to the lexer state (borrowed).
 * @return true when the current token has an operator type (not NONE/word).
 */
bool	is_in_middle_of_operator(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Tests whether the current character can extend a '<' operator.
 * @param state Pointer to the lexer state (borrowed).
 * @return true if the current character continues a less-than operator.
 */
bool	is_operator_char_less(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Tests whether the current character can extend a '|' operator.
 * @param state Pointer to the lexer state (borrowed).
 * @return true if the current character continues a pipe operator.
 */
bool	is_operator_char_pipe(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Tests whether the current character can extend a '>' operator.
 * @param state Pointer to the lexer state (borrowed).
 * @return true if the current character continues a greater-than operator.
 */
bool	is_operator_char_great(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Tests whether the current character can extend a ';' operator.
 * @param state Pointer to the lexer state (borrowed).
 * @return true if the current character continues a semicolon operator.
 */
bool	is_operator_char_semicolon(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Tests whether the current character can extend a '&' operator.
 * @param state Pointer to the lexer state (borrowed).
 * @return true if the current character continues an ampersand operator.
 */
bool	is_operator_char_ampersand(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Consumes a '<'-family operator character, refining its token type.
 *
 * Extends the operator into LESS, DLESS, DLESSDASH, LESSAND or LESSGREAT as
 * the following characters dictate.
 *
 * @param state Pointer to the lexer state (borrowed).
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	operator_add_less(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Consumes a '|'-family operator character (PIPE or OR_IF).
 * @param state Pointer to the lexer state (borrowed).
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	operator_add_pipe(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Consumes a '>'-family operator character, refining its token type.
 *
 * Extends the operator into GREAT, DGREAT, GREATAND or CLOBBER as the
 * following characters dictate.
 *
 * @param state Pointer to the lexer state (borrowed).
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	operator_add_great(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Consumes a ';'-family operator character (SCOLON, DSEMI or SEMI_AND).
 * @param state Pointer to the lexer state (borrowed).
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	operator_add_semicolon(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Consumes a '&'-family operator character (AMPERSAND or AND_IF).
 * @param state Pointer to the lexer state (borrowed).
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	operator_add_ampersand(t_lexer *state);

#endif
