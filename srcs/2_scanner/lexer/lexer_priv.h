#ifndef LEXER_PRIV_H
# define LEXER_PRIV_H

# include "lexer.h"

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

/**
 * @ingroup lexer
 * @brief Rebinds @c lexer->input to the top of the input stack, optionally
 *        pushing @p input first as a new stack item.
 *
 * @warning When @p input is NULL the stack must already be non-empty
 *          (@ref lexer_input_stack_get_last asserts).
 * @warning On push failure the text is handed back to @p input and the
 *          caller keeps ownership of it.
 *
 * @param lexer Already initialized lexer (borrowed).
 * @param input Text to push, or NULL to only rebind; must be initialized by
 *              the caller, left holding an empty string on success
 *              (borrowed; ownership of the text taken by the input stack).
 * @return @c ERR_NO on success, @c ERR_LIBC on allocation failure.
 */
t_error	bind_lexer_input(t_lexer *lexer, t_string *input);

/**
 * @ingroup lexer
 * @brief Releases the token binding without touching the token: called at
 *        every recognition exit (token delivered to the caller, or error)
 *        so the next @ref bind_lexer_token initializes fresh storage.
 *
 * @param lexer Already initialized lexer (borrowed).
 */
void	unbind_lexer_token(t_lexer *lexer);

#endif
