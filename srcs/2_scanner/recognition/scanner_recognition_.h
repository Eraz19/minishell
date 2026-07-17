#ifndef SCANNER_RECOGNITION__H
# define SCANNER_RECOGNITION__H

# include "lexer.h"

/** @defgroup scanner_recognition Scanner recognition
 *  @brief POSIX token-recognition rules driving the lexer.
 *
 *  These rules are the scanner's plug-in for @c lexer_get_next_token: the
 *  dispatcher @ref scanner_recognize applies one POSIX 2.3 rule to the
 *  current character, building word, operator, blank and comment tokens on
 *  top of the generic lexer engine and its context toolkit.
 */

/* ************************************************************************* */
/*                                 DISPATCH                                  */
/* ************************************************************************* */

/**
 * @ingroup scanner_recognition
 * @brief Applies one POSIX token-recognition rule to the current character.
 *
 * Tested in POSIX 2.3 order: end of input (rule 1), operator in progress
 * (rules 2-3), quoting (rule 4), expansion (rule 5), new operator
 * (rule 6), blank (rule 7), in-word (rule 8), comment (rule 9), then new
 * word (rule 10).
 *
 * @param lexer Lexer state (borrowed).
 * @param context Set to the quoting or expansion context detected by
 *                rules 4 and 5, untouched otherwise (borrowed).
 * @return @c ERR_LIBC on allocation failure; @c ERR_INCOHERENT_STATE on an
 *         operator dispatch inconsistency; from the quoting and expansion
 *         rules of the lexer context engine: @c ERR_UNEXPECTED_EOI or
 *         @c ERR_VEOF (end of input inside a construct),
 *         @c ERR_CTX_END_NOT_FOUND, @c ERR_NO_INPUT_TO_LEX,
 *         @c ERR_EMPTY_STACK, @c ERR_NOT_IMPLEMENTED; @c ERR_NO on
 *         success.
 */
t_error	scanner_recognize(t_lexer *lexer, t_context *context);

/* ************************************************************************* */
/*                                PREDICATES                                 */
/* ************************************************************************* */

/**
 * @ingroup scanner_recognition
 * @brief Tells whether the current character starts a comment: @c '#'.
 *
 * @param lexer Lexer state (borrowed, read-only).
 */
bool	is_comment(t_lexer *lexer);

/**
 * @ingroup scanner_recognition
 * @brief Tells whether the current input is exhausted: @c '\0'.
 *
 * @param lexer Lexer state (borrowed, read-only).
 */
bool	is_end(t_lexer *lexer);

/**
 * @ingroup scanner_recognition
 * @brief Tells whether an operator token is being built: the current
 *        token has a type other than @c TOKEN_NONE and @c TOKEN_TOKEN.
 *
 * @param lexer Lexer state (borrowed, read-only).
 */
bool	is_in_middle_of_operator(t_lexer *lexer);

/**
 * @ingroup scanner_recognition
 * @brief Tells whether a word token is being built: the current token is
 *        a @c TOKEN_TOKEN.
 *
 * @param lexer Lexer state (borrowed, read-only).
 */
bool	is_in_middle_of_word(t_lexer *lexer);

/**
 * @ingroup scanner_recognition
 * @brief Tells whether the current character starts a new operator: an
 *        operator character while no operator is in progress.
 *
 * @param lexer Lexer state (borrowed, read-only).
 */
bool	is_new_operator(t_lexer *lexer);

/* ************************************************************************* */
/*                                   RULES                                   */
/* ************************************************************************* */

/**
 * @ingroup scanner_recognition
 * @brief Rule 7: delimits the pending token, or skips consecutive blanks
 *        when no token is pending.
 *
 * @param lexer Lexer state (borrowed).
 * @return The lexer's recorded error: the rule raises none itself.
 */
t_error	lexer_rule_blank(t_lexer *lexer);

/**
 * @ingroup scanner_recognition
 * @brief Rule 9: discards every character up to (excluded) the next
 *        newline or end of input.
 *
 * @param lexer Lexer state (borrowed).
 */
void	lexer_rule_comment(t_lexer *lexer);

/**
 * @ingroup scanner_recognition
 * @brief Rule 1: delimits the pending token at end of input, emitting a
 *        @c TOKEN_EOF token when none is pending.
 *
 * @param lexer Lexer state (borrowed).
 * @return The lexer's recorded error: the rule raises none itself.
 */
t_error	lexer_rule_end(t_lexer *lexer);

/**
 * @ingroup scanner_recognition
 * @brief Rules 2-3: appends the current character to the operator in
 *        progress when it can extend it, otherwise delimits it.
 *
 * @param lexer Lexer state (borrowed).
 * @return @c ERR_LIBC on allocation failure, @c ERR_INCOHERENT_STATE on an
 *         operator dispatch inconsistency, @c ERR_NO on success.
 */
t_error	lexer_rule_in_middle_of_operator(t_lexer *lexer);

/**
 * @ingroup scanner_recognition
 * @brief Rule 8: appends the current character to the word in progress,
 *        handling top-level backslash escaping and recording the first
 *        unquoted @c '=' as the token's assignment offset.
 *
 * @note A line continuation ending the input is benign (POSIX 2.2.1:
 *       removed before tokenization): the scan resumes at rule 1.
 *
 * @param lexer Lexer state (borrowed).
 * @return @c ERR_LIBC on allocation failure; @c ERR_NO on success.
 */
t_error	lexer_rule_in_middle_of_word(t_lexer *lexer);

/**
 * @ingroup scanner_recognition
 * @brief Rule 6: delimits the pending word, or starts the new operator
 *        when no token is pending.
 *
 * Before @c '<' or @c '>', the pending word is requalified as
 * @c TOKEN_IO_NUMBER when it is solely digits, or as
 * @c TOKEN_IO_LOCATION when it is at least three characters starting
 * with @c '{' and ending with @c '}'.
 *
 * @param lexer Lexer state (borrowed).
 * @return @c ERR_LIBC on allocation failure, @c ERR_INCOHERENT_STATE on an
 *         operator dispatch inconsistency, @c ERR_NO on success.
 */
t_error	lexer_rule_new_operator(t_lexer *lexer);

/**
 * @ingroup scanner_recognition
 * @brief Rule 10: starts a new word from the current character, handling
 *        top-level backslash escaping.
 *
 * @note A line continuation ending the input is benign (POSIX 2.2.1:
 *       removed before tokenization): the scan resumes at rule 1.
 *
 * @param lexer Lexer state (borrowed).
 * @return @c ERR_LIBC on allocation failure; @c ERR_NO on success.
 */
t_error	lexer_rule_new_word(t_lexer *lexer);

/* ************************************************************************* */
/*                                 OPERATORS                                 */
/* ************************************************************************* */

/**
 * @ingroup scanner_recognition
 * @brief Tells whether the current character can start or extend the
 *        operator in progress, dispatching on the character.
 *
 * @param lexer Lexer state (borrowed, read-only).
 */
bool	is_operator_char(t_lexer *lexer);

/**
 * @ingroup scanner_recognition
 * @brief Tells whether @c '&' can start or extend the operator in
 *        progress (@c ';', @c '&', @c '<' or @c '>' tokens).
 *
 * @param lexer Lexer state (borrowed, read-only).
 */
bool	is_operator_char_ampersand(t_lexer *lexer);

/**
 * @ingroup scanner_recognition
 * @brief Tells whether @c '>' can start or extend the operator in
 *        progress (@c '<' or @c '>' tokens).
 *
 * @param lexer Lexer state (borrowed, read-only).
 */
bool	is_operator_char_great(t_lexer *lexer);

/**
 * @ingroup scanner_recognition
 * @brief Tells whether @c '<' can start or extend the operator in
 *        progress (@c '<' token).
 *
 * @param lexer Lexer state (borrowed, read-only).
 */
bool	is_operator_char_less(t_lexer *lexer);

/**
 * @ingroup scanner_recognition
 * @brief Tells whether @c '|' can start or extend the operator in
 *        progress (@c '|' or @c '>' tokens).
 *
 * @param lexer Lexer state (borrowed, read-only).
 */
bool	is_operator_char_pipe(t_lexer *lexer);

/**
 * @ingroup scanner_recognition
 * @brief Tells whether @c ';' can start or extend the operator in
 *        progress (@c ';' token).
 *
 * @param lexer Lexer state (borrowed, read-only).
 */
bool	is_operator_char_semicolon(t_lexer *lexer);

/**
 * @ingroup scanner_recognition
 * @brief Consumes the current character into the operator token,
 *        dispatching on the character to build the right operator type.
 *
 * @param lexer Lexer state (borrowed).
 * @return @c ERR_LIBC on allocation failure, @c ERR_INCOHERENT_STATE when
 *         the character is not an operator character, @c ERR_NO on
 *         success.
 */
t_error	lexer_add_char_into_token_operator(t_lexer *lexer);

/**
 * @ingroup scanner_recognition
 * @brief Consumes @c '&', building @c TOKEN_SEMI_AND, @c TOKEN_AND_IF,
 *        @c TOKEN_LESSAND, @c TOKEN_GREATAND or @c TOKEN_AMPERSAND from
 *        the operator in progress.
 *
 * @param lexer Lexer state (borrowed).
 * @return @c ERR_LIBC on allocation failure, @c ERR_INCOHERENT_STATE when
 *         the pending token cannot be extended by @c '&', @c ERR_NO on
 *         success.
 */
t_error	operator_add_ampersand(t_lexer *lexer);

/**
 * @ingroup scanner_recognition
 * @brief Consumes @c '>', building @c TOKEN_LESSGREAT, @c TOKEN_DGREAT or
 *        @c TOKEN_GREAT from the operator in progress.
 *
 * @param lexer Lexer state (borrowed).
 * @return @c ERR_LIBC on allocation failure, @c ERR_INCOHERENT_STATE when
 *         the pending token cannot be extended by @c '>', @c ERR_NO on
 *         success.
 */
t_error	operator_add_great(t_lexer *lexer);

/**
 * @ingroup scanner_recognition
 * @brief Consumes @c '<', building @c TOKEN_DLESS or @c TOKEN_LESS from
 *        the operator in progress.
 *
 * @param lexer Lexer state (borrowed).
 * @return @c ERR_LIBC on allocation failure, @c ERR_INCOHERENT_STATE when
 *         the pending token cannot be extended by @c '<', @c ERR_NO on
 *         success.
 */
t_error	operator_add_less(t_lexer *lexer);

/**
 * @ingroup scanner_recognition
 * @brief Consumes @c '|', building @c TOKEN_OR_IF, @c TOKEN_CLOBBER or
 *        @c TOKEN_PIPE from the operator in progress.
 *
 * @param lexer Lexer state (borrowed).
 * @return @c ERR_LIBC on allocation failure, @c ERR_INCOHERENT_STATE when
 *         the pending token cannot be extended by @c '|', @c ERR_NO on
 *         success.
 */
t_error	operator_add_pipe(t_lexer *lexer);

/**
 * @ingroup scanner_recognition
 * @brief Consumes @c ';', building @c TOKEN_DSEMI or @c TOKEN_SCOLON from
 *        the operator in progress.
 *
 * @param lexer Lexer state (borrowed).
 * @return @c ERR_LIBC on allocation failure, @c ERR_INCOHERENT_STATE when
 *         the pending token cannot be extended by @c ';', @c ERR_NO on
 *         success.
 */
t_error	operator_add_semicolon(t_lexer *lexer);

#endif
