#ifndef TOKEN_RECOGNITION_CONTEXT_SCAN_PRIV_H
# define TOKEN_RECOGNITION_CONTEXT_SCAN_PRIV_H

# include "lexer.h"

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup lexer
 * @brief End-of-input continuation while a construct is open: pops an
 *        exhausted alias input so the construct scan resumes on the outer
 *        input (POSIX 2.3.1 splice — the token under construction
 *        survives), or requests a PS2 continuation from the scanner, or
 *        reports the construct as unterminated.
 *
 * @note @c ERR_NO means a continuation line was appended to the current
 *       input: the caller's scan loop resumes with the cursor on the first
 *       appended character. Both end-of-continuation reports — the
 *       no-continuation-possible @c ERR_POSIX_SYNTAX and the interactive
 *       @c CTRL+D @c ERR_VEOF — are converted into the
 *       @ref error_unterminated_construct diagnostic.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @return @c ERR_POSIX_SYNTAX (printed) when the input ends for good —
 *         no continuation possible, or interactive @c CTRL+D at PS2 —
 *         (named or generic diagnostic, see
 *         @ref error_unterminated_construct); @c ERR_LIBC (failed
 *         allocation or libc call); @c ERR_NO after an alias pop (the
 *         construct scan resumes on the outer input) or an appended PS2
 *         continuation. Module-external errors (params, sig, embedded
 *         command-substitution parse) bubble through unlisted.
 */
t_error	on_context_scan_EOI(t_lexer *lexer);

/* ************************************************************************* */
/*                                 ERROR                                     */
/* ************************************************************************* */

/**
 * @ingroup lexer
 * @brief Prints the end-of-input diagnostic: names the innermost OPEN
 *        context of the current token (walking @c token->contexts from
 *        the back for the first @c end @c == @c SIZE_MAX sentinel, see
 *        @ref t_context_stack_item), or falls back to the generic
 *        "unexpected end of input" when nothing is open (empty stack or
 *        closed spans only, e.g. a trailing line continuation).
 *
 * @note Expects @c lexer->err to hold the end-of-continuation report:
 *       an @c ERR_VEOF (interactive @c CTRL+D at PS2) is retyped to a
 *       fresh @c ERR_POSIX_SYNTAX — mandatory, as @c ERR_VEOF is born
 *       with @c printed set and would both skip the diagnostic and make
 *       the shell exit mid-continuation — while the unprinted
 *       @c ERR_POSIX_SYNTAX of the no-continuation gates keeps its
 *       descriptor.
 *
 * @note The printed result is mirrored back into @c lexer->err:
 *       @ref scan_context propagates errors through @c lexer->err, not
 *       through hook return values, so an unmirrored @c printed flag
 *       would get the diagnostic reprinted (generic form) at the scanner
 *       exit frontier.
 *
 * @param lexer Already initialized lexer holding the end-of-continuation
 *              report in @c err; the token context stack may be empty
 *              (borrowed).
 * @return @c ERR_POSIX_SYNTAX (printed), always — retyped at production,
 *         so the scanner endpoint passes it through verbatim; also
 *         mirrored into @c lexer->err.
 */
t_error	error_unterminated_construct(t_lexer *lexer);

#endif
