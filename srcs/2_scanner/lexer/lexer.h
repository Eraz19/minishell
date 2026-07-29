#ifndef LEXER_H
# define LEXER_H

# include "token.h"
# include "error.h"
# include "lexer_input_stack.h"

/**
 * @defgroup lexer Lexer API
 * @brief POSIX shell token recognizer.
 *
 * The lexer walks the current input text and produces one token per
 * @ref lexer_get_next_token call, applying the POSIX token recognition
 * rules (operators, blanks, comments, quoting and expansion contexts).
 * Inputs are stacked so an alias expansion can be lexed in place of the
 * word that produced it, then popped to resume the outer input.
 */

/* ************************************************************************* */
/*                             TYPE FORWARDING                               */
/* ************************************************************************* */

typedef struct s_scanner					t_scanner;
typedef struct s_token_recognition_context	t_token_recognition_context;

/* ************************************************************************* */
/*                                  TYPES                                    */
/* ************************************************************************* */

/**
 * @ingroup lexer
 * @struct s_lexer
 * @brief Token recognizer state bound to one scanner.
 *
 * @var s_lexer::err Last error produced by a lexer operation.
 * @var s_lexer::input Current input item, referencing the top of
 *                     @c input_stack (borrowed).
 * @var s_lexer::token Token under construction; bound for the duration
 *                     of one recognition and released by
 *                     @ref unbind_lexer_token at every
 *                     @ref lexer_get_next_token / @ref lexer_scan_word
 *                     exit — @ref bind_lexer_token initializes only on a
 *                     NULL binding, so a non-NULL value marks an
 *                     in-flight recognition (borrowed).
 * @var s_lexer::scanner Scanner owning this lexer, used to request PS2
 *                       continuations at end of input (borrowed).
 * @var s_lexer::last_index Source span of the last token consumed from the
 *                          root input; reused as the span of tokens lexed
 *                          from alias expansions.
 * @var s_lexer::input_stack Root input plus pushed alias expansions,
 *                           managed by the lexer_input_stack submodule.
 * @var s_lexer::emited_token True once the current token has been
 *                            delimited; ends the recognition loop.
 */
typedef struct s_lexer
{
	t_error						err;
	t_lexer_input_stack_item	*input;
	t_token						*token;
	t_scanner					*scanner;
	t_token_index				last_index;
	t_lexer_input_stack			input_stack;
	bool						emited_token;
}	t_lexer;

/* ************************************************************************* */
/*                                LIFE_CYCLE                                 */
/* ************************************************************************* */

/**
 * @ingroup lexer
 * @brief Zeroes @p lexer, binds it to @p scanner and initializes an empty
 *        input stack.
 *
 * @param lexer Lexer to initialize; initialized by the function (borrowed).
 * @param scanner Scanner the lexer reports to; stored for the whole lexer
 *                lifetime (borrowed).
 */
void	lexer_init(t_lexer *lexer, t_scanner *scanner);

/**
 * @ingroup lexer
 * @brief Releases the input stack and resets every field of @p lexer.
 *
 * @param lexer Already initialized lexer (borrowed).
 */
void	lexer_free(t_lexer *lexer);

/**
 * @ingroup lexer
 * @brief Pops every stacked input and resets the cursor state, keeping the
 *        @c scanner binding so @p lexer can be reused.
 *
 * @param lexer Already initialized lexer (borrowed).
 */
void	lexer_clear(t_lexer *lexer);

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup lexer
 * @brief Lexes the next token from the current input, requesting PS2
 *        continuations on end of input and popping finished alias inputs.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @param out Receives the token; initialized by the function. The caller
 *            releases it with @ref token_free (borrowed).
 * @return @c ERR_NO on success. Module-produced failures: @c ERR_LIBC
 *         (failed allocation or libc call), @c ERR_POSIX_SYNTAX (printed,
 *         construct left open — or trailing line continuation — when no
 *         more input is possible in any mode, see
 *         @ref error_unterminated_construct) and @c ERR_VEOF (end of
 *         input reported by the PS2 continuation request).
 *         Module-external errors (embedded command-substitution parse,
 *         params, sig) bubble through unlisted.
 */
t_error	lexer_get_next_token(t_lexer *lexer, t_token *out);

/**
 * @ingroup lexer
 * @brief Scans @p src as one word with the @p args rules: pushes it as the
 *        current input, binds @p out as the token under construction and
 *        runs @ref scan_context until the rules' end condition.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @param out Receives the scanned token; initialized by the function,
 *            untouched when pushing @p src fails. The caller releases it
 *            with @ref token_free (borrowed).
 * @param src Text to scan; must be initialized by the caller, left holding
 *            an empty string except when pushing it fails, where the
 *            caller keeps the text (borrowed; ownership of the text taken
 *            by the input stack).
 * @param args Rule set of the scan; its @c context_item is freed by the
 *             function on every path (borrowed).
 * @return @c ERR_NO on success; the @ref scan_context failure set:
 *         @c ERR_LIBC, @c ERR_POSIX_SYNTAX (printed) and @c ERR_VEOF,
 *         with module-external errors bubbling through unlisted.
 */
t_error	lexer_scan_word(t_lexer *lexer, t_token *out, t_string *src,
			t_token_recognition_context *args);

/**
 * @ingroup lexer
 * @brief Pops the finished top input and rebinds @c lexer->input to the
 *        new top; then, between tokens (the current token is the
 *        @c TOKEN_EOF placeholder) it is reset, unbound and relexed from
 *        the outer input, while mid-construct the token is left untouched
 *        and the caller's construct scan resumes on the outer input
 *        (POSIX 2.3.1: the alias value is spliced into the input stream,
 *        an open construct continues past it).
 *
 * @warning The input stack must hold at least two items: the root input is
 *          never popped.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @return @c ERR_NO on the mid-construct lane (the scan loop continues);
 *         otherwise the result of the relex, same set as
 *         @ref lexer_get_next_token.
 */
t_error	lexer_pop_alias(t_lexer *lexer);

/**
 * @ingroup lexer
 * @brief Pushes @p alias as the new current input, frees the token under
 *        construction and lexes the next token from the alias body.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @param alias Alias expansion to lex (ownership taken by the input stack).
 * @warning On @c ERR_LIBC push failure the item is not stacked and the
 *          caller keeps ownership of @p alias.
 * @return @c ERR_LIBC if the push fails; otherwise the result of the
 *         relex; same set as @ref lexer_get_next_token.
 */
t_error	lexer_push_alias(t_lexer *lexer, t_lexer_input_stack_item *alias);

#endif
