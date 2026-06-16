/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_rules_.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 15:10:54 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/16 00:09:51 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_RULES__H
# define LEXER_RULES__H

# include "lexer_.h"

/**
 * @ingroup scanner
 * @brief Tests whether the cursor is at end-of-input (NUL).
 * @param state Pointer to the lexer state (borrowed).
 * @return true if the current character is '\0'.
 */
bool	is_end(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Tests whether the current character starts a comment ('#').
 *
 * Only meaningful when not in the middle of a word; the dispatcher checks the
 * word rule first so a '#' inside a word stays literal.
 *
 * @param state Pointer to the lexer state (borrowed).
 * @return true if the current character is '#'.
 */
bool	is_comment(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Tests whether a new operator starts here.
 * @param state Pointer to the lexer state (borrowed).
 * @return true if not mid-operator and the current character is an operator.
 */
bool	is_new_operator(t_lexer *state);

/**
 * @ingroup scanner
 * @brief Tests whether a word token is currently being built.
 * @param state Pointer to the lexer state (borrowed).
 * @return true if the current token is a word.
 */
bool	is_in_middle_of_word(t_lexer *state);

/**
 * @ingroup scanner
 * @brief POSIX rule 1: end-of-input delimits the current token (or stops).
 * @param state Pointer to the lexer state (borrowed).
 * @return ERR_NO; delimits a pending token or marks end-of-input.
 */
t_error	lexer_rule_end(t_lexer *state);								// Rule 1

/**
 * @ingroup scanner
 * @brief POSIX rule 7: a blank delimits a pending token, else it is skipped.
 * @param state Pointer to the lexer state (borrowed).
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	lexer_rule_blank(t_lexer *state);							// Rule 7

/**
 * @ingroup scanner
 * @brief POSIX rule 9: discards a comment to the end of the line.
 * @param state Pointer to the lexer state (borrowed).
 */
void	lexer_rule_comment(t_lexer *state);							// Rule 9

/**
 * @ingroup scanner
 * @brief POSIX rule 10: begins a new word with the current character.
 * @param state Pointer to the lexer state (borrowed).
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	lexer_rule_new_word(t_lexer *state);						// Rule 10

/**
 * @ingroup scanner
 * @brief POSIX rule 6: a new operator delimits a pending word, else it starts.
 * @param state Pointer to the lexer state (borrowed).
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	lexer_rule_new_operator(t_lexer *state);					// Rule 6

/**
 * @ingroup scanner
 * @brief POSIX rule 8: appends the current character to the current word.
 *
 * Handles a leading backslash as a top-level escape (with line continuation).
 *
 * @param state Pointer to the lexer state (borrowed).
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	lexer_rule_in_middle_of_word(t_lexer *state);				// Rule 8

/**
 * @ingroup scanner
 * @brief POSIX rules 2-3: extend the operator, or delimit it when it cannot.
 * @param state Pointer to the lexer state (borrowed).
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	lexer_rule_in_middle_of_operator(t_lexer *state);			// Rule 2-3

/**
 * @ingroup scanner
 * @brief POSIX rule 4: scans a quoting construct, keeping it in the word.
 * @param state Pointer to the lexer state (borrowed).
 * @param context Quoting context detected at the cursor.
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	lexer_rule_quoting(t_lexer *state, t_context context);		// Rule 4

/**
 * @ingroup scanner
 * @brief POSIX rule 5: scans an expansion construct, keeping it in the word.
 *
 * For an arithmetic context, falls back to command substitution when the
 * "$((" turns out not to close as arithmetic.
 *
 * @param state Pointer to the lexer state (borrowed).
 * @param context Expansion context detected at the cursor.
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	lexer_rule_expansion(t_lexer *state, t_context context);	// Rule 5

#endif
