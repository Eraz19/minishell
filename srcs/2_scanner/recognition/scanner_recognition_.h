#ifndef SCANNER_RECOGNITION__H
# define SCANNER_RECOGNITION__H

# include "lexer.h"

/** @defgroup scanner
 *  @brief POSIX token-recognition rules driving the lexer.
 *
 *  These rules are the scanner's plug-in for lexer_get_next_token: the
 *  dispatcher scanner_recognize() applies one POSIX 2.3 rule to the current
 *  character, building word, operator, blank and comment tokens on top of the
 *  generic lexer engine and its context toolkit.
 */

/**
 * @ingroup scanner
 * @brief Applies one POSIX token-recognition rule to the current character.
 *
 * Tested in POSIX 2.3 order: end-of-input, operator-in-progress, quoting,
 * expansion, new operator, blank, in-word, comment, then new word.
 *
 * @param lexer Pointer to the lexer state (borrowed).
 * @param context Out-parameter receiving the detected context, if any.
 * @return ERR_NO on success, or the recorded error on failure.
 */
t_error	scanner_recognize(t_lexer *lexer, t_context *context);

bool	is_end(t_lexer *lexer);
bool	is_comment(t_lexer *lexer);
bool	is_new_operator(t_lexer *lexer);
bool	is_in_middle_of_word(t_lexer *lexer);
bool	is_in_middle_of_operator(t_lexer *lexer);

t_error	lexer_rule_end(t_lexer *lexer);
t_error	lexer_rule_blank(t_lexer *lexer);
void	lexer_rule_comment(t_lexer *lexer);
t_error	lexer_rule_new_word(t_lexer *lexer);
t_error	lexer_rule_new_operator(t_lexer *lexer);
t_error	lexer_rule_in_middle_of_word(t_lexer *lexer);
t_error	lexer_rule_in_middle_of_operator(t_lexer *lexer);

bool	is_operator_char(t_lexer *lexer);
t_error	lexer_add_char_into_token_operator(t_lexer *lexer);

bool	is_operator_char_less(t_lexer *lexer);
bool	is_operator_char_pipe(t_lexer *lexer);
bool	is_operator_char_great(t_lexer *lexer);
bool	is_operator_char_semicolon(t_lexer *lexer);
bool	is_operator_char_ampersand(t_lexer *lexer);

t_error	operator_add_less(t_lexer *lexer);
t_error	operator_add_pipe(t_lexer *lexer);
t_error	operator_add_great(t_lexer *lexer);
t_error	operator_add_semicolon(t_lexer *lexer);
t_error	operator_add_ampersand(t_lexer *lexer);

#endif
