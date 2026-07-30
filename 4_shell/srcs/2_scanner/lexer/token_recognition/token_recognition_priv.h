#ifndef	TOKEN_RECOGNITION_PRIV_H
# define TOKEN_RECOGNITION_PRIV_H

# include "lexer.h"

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup lexer
 * @brief Moves the read cursor of the current input forward by @p offset
 *        characters, without consuming them into the token value.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @param offset Number of characters to skip.
 */
void	token_recognition_advance(t_lexer *lexer, size_t offset);

/**
 * @ingroup lexer
 * @brief Appends the next @p iter input characters to the token value,
 *        sets the token type to @p type and updates the token source span.
 *
 * @note While lexing an alias expansion (stacked input), the span of the
 *       originating word (@c lexer->last_index) is used instead of the
 *       cursor position.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @param type Token type to assign.
 * @param iter Number of characters to consume.
 * @return @c ERR_NO on success, @c ERR_LIBC if growing the token value
 *         fails.
 */
t_error	token_recognition_consume(t_lexer *lexer, t_token_type type, size_t iter);

/**
 * @ingroup lexer
 * @brief Marks the current token as emitted, ending the recognition loop;
 *        an empty token gets a collapsed source span.
 *
 * @param lexer Already initialized lexer (borrowed).
 */
void	token_recognition_delimit(t_lexer *lexer);

/* ************************************************************************* */
/*                                COMMENT                                    */
/* ************************************************************************* */

/**
 * @ingroup lexer
 * @brief Returns true when the current input character starts a comment
 *        (@c #).
 *
 * @param lexer Already initialized lexer (borrowed, read-only).
 */
bool	is_comment_start(t_lexer *lexer);

/* ************************************************************************* */
/*                                  WORD                                     */
/* ************************************************************************* */

/**
 * @ingroup lexer
 * @brief Returns true when a word token (@c TOKEN_TOKEN) is under
 *        construction.
 *
 * @param lexer Already initialized lexer (borrowed, read-only).
 */
bool	is_inside_word(t_lexer *lexer);

/* ************************************************************************* */
/*                                 RULES                                     */
/* ************************************************************************* */

/**
 * @ingroup lexer
 * @brief Blank rule: delimits the token in progress, or skips consecutive
 *        blanks when no token has started.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @return @c ERR_NO.
 */
t_error	recognize_token_blank_delimiter(t_lexer *lexer);

/**
 * @ingroup lexer
 * @brief Comment rule: discards every character up to (excluding) the next
 *        newline or end of input.
 *
 * @param lexer Already initialized lexer (borrowed).
 */
void	recognize_token_escape_comment(t_lexer *lexer);

/**
 * @ingroup lexer
 * @brief End-of-input rule: delimits the token in progress, or emits
 *        @c TOKEN_EOF when no token has started.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @return @c ERR_NO.
 */
t_error	recognize_token_input_end(t_lexer *lexer);

/**
 * @ingroup lexer
 * @brief Operator rules 2-3: extends the operator in progress when the
 *        current character still fits it, otherwise delimits it.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @return @c ERR_NO on success, @c ERR_LIBC on allocation failure; a token
 *         state matching no operator continuation is asserted out (debug
 *         builds), not reported.
 */
t_error	recognize_token_inside_operator(t_lexer *lexer);

/**
 * @ingroup lexer
 * @brief Word rule 8: consumes the current character into the word,
 *        handling @c \\ escapes and recording the first unquoted @c = for
 *        assignment detection.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @return @c ERR_NO on success, @c ERR_LIBC on allocation failure; a
 *         trailing escape triggers the end-of-input continuation, adding
 *         the @ref on_context_scan_EOI module set (@c ERR_POSIX_SYNTAX
 *         printed, @c ERR_VEOF, @c ERR_LIBC) with module-external errors
 *         bubbling through unlisted.
 */
t_error	recognize_token_inside_word(t_lexer *lexer);

/**
 * @ingroup lexer
 * @brief Operator rule 6: delimits the token in progress before an
 *        operator starts (requalifying it as @c TOKEN_IO_NUMBER or
 *        @c TOKEN_IO_LOCATION before a redirection), or begins the new
 *        operator.
 *
 * @note @c TOKEN_IO_LOCATION applies the minimal POSIX 2.10.1 lexical
 *       rule verbatim — at least three characters, starts @c { , ends
 *       @c } , delimiter @c < or @c > — with no validation of the
 *       enclosed location (documented choice: the rule says IO_LOCATION
 *       "may result" and 2.7 leaves the format implementation-defined;
 *       every such word before a redirection IS a location here, and an
 *       invalid one fails at redirection time in the runner — unlike
 *       bash, which lexes non-NAME contents as a plain word).
 *
 * @param lexer Already initialized lexer (borrowed).
 * @return @c ERR_NO on success, @c ERR_LIBC on allocation failure; a token
 *         state matching no operator start is asserted out (debug builds),
 *         not reported.
 */
t_error	recognize_token_new_operator(t_lexer *lexer);

/**
 * @ingroup lexer
 * @brief Word rule 10: starts a new word token from the current character,
 *        handling @c \\ escapes.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @return @c ERR_NO on success, @c ERR_LIBC on allocation failure; a
 *         trailing escape triggers the end-of-input continuation, adding
 *         the @ref on_context_scan_EOI module set (@c ERR_POSIX_SYNTAX
 *         printed, @c ERR_VEOF, @c ERR_LIBC) with module-external errors
 *         bubbling through unlisted.
 */
t_error	recognize_token_new_word(t_lexer *lexer);

/**
 * @ingroup lexer
 * @brief Quoting rule: scans the quoting construct opening at the cursor
 *        into the current word token.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @param context Quoting construct to scan (@c CONTEXT_SQUOTE,
 *                @c CONTEXT_DQUOTE or @c CONTEXT_DOLLAR_SQUOTE).
 * @return @c ERR_NO on success; @c ERR_LIBC, @c ERR_POSIX_SYNTAX
 *         (printed) or @c ERR_VEOF on module-produced failure (see
 *         @ref recognize_token for the failure conditions), with
 *         module-external errors bubbling through unlisted.
 */
t_error	recognize_token_quoting_context(t_lexer *lexer, t_context context);

#endif
