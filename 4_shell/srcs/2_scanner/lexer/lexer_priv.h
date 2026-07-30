#ifndef LEXER_PRIV_H
# define LEXER_PRIV_H

# include "lexer.h"

/* ************************************************************************* */
/*                                    OPS                                    */
/* ************************************************************************* */

void	bind_lexer_input(t_lexer *lexer);

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
